import socket  # 导入 socket 模块
import pymysql
from copy import deepcopy
from globals import * # 格式规定作为全局变量

expe = True


class my_server():
    def __init__(self, ip, port=8888): #实例化时需给定IP地址，对服务器端可给定为本机地址并设置固定ip地址
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建 socket 对象，使用tcp协议
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # 设置地址可重用
        self.server.bind((ip, port))  # 绑定端口
        self.info = information()
        self.recommend_list = list()
        self.weight = weight()
        self.client = None
        self.client_addr = None
        self.rec_num = 0

    def conn(self, connect_number=5):
        self.server.listen(connect_number)  # 等待客户端连接
        self.client, self.client_addr = self.server.accept()  # 建立客户端连接
        print('Connected successfully', self.client_addr)

    def send(self, msg):  #采用utf-8编码，缓冲默认大小为1024
        self.client.send(msg.encode('utf-8'))
    def recv(self, buffer=1024):
         return self.client.recv(buffer).decode('utf-8')
    def confirm(self):  #用于确认对方已经收到消息
        if self.recv()=='OK':
            return 0
        elif self.recv()=='error':
            return 1
        else:
            return -1

    def recommend(self, expe=False):  # 基于关系网络
        self.recommend_list = list()
        for i in range(self.rec_num):
            self.recommend_list += [information()]
        current_num = 0
        if expe:
            tb_str = "sciexp"
        else:
            tb_str = "paperinfo"
        idx_list = [0.] * self.rec_num
        db = pymysql.connect("localhost", "root", "123456", db="scidb", charset='utf8')  # 连接数据库
        cursor = db.cursor()
        print("Success in Connecting to MySQL")
        cursor.execute('select' + ' * from ' + tb_str)

        while True:
            row = cursor.fetchone()
            if not row:
                break
            # print(row)
            tmp_info = information()
            tmp_info.set_title(row[1])
            for i in range(len_author):
                tmp_info.set_author(row[2+i], i)
            for i in range(len_key):
                tmp_info.set_key_word(row[2+len_author+i], i)
            tmp_info.set_origin(row[2+len_author+len_key])
            tmp_info.set_date(row[3+len_author+len_key])
            for i in range(len_ref):
                tmp_info.set_ref(row[4+len_author+len_key+i], i)
            tmp_info.set_doi(row[4 + len_author + len_key+len_ref])
            tmp_info.set_abstract(row[5 + len_author + len_key + len_ref])
            tmp_info.set_database(row[6 + len_author + len_key + len_ref])
            tmp_info.set_cite_number(row[7 + len_author + len_key + len_ref])
            for i in range(len_field):
                tmp_info.set_field(row[8 + len_author + len_key + len_ref + i], i)

            score = correlation(tmp_info, self.info, self.weight)
            if current_num < self.rec_num:
                if score >= 0.:
                    idx_list[current_num] = score
                    self.recommend_list[current_num].copy(tmp_info)
                    # print(tmp_info.content)
                    current_num += 1
            else:
                min_score = idx_list[0]
                min_idx = 0
                for i in range(self.rec_num):
                    if idx_list[i] < min_score:
                        min_score = idx_list[i]
                        min_idx = i
                if score > min_score or (score == min_score and int(tmp_info.content['cite_number']) > int(self.recommend_list[min_idx].content['cite_number'])):
                    idx_list[min_idx] = score
                    self.recommend_list[min_idx].copy(tmp_info)
                    # print(tmp_info.content)
                current_num += 1

        cursor.close()
        db.close()
        print("Current Num: " + str(current_num))
        # if current_num < self.rec_num:
        #     for i in range(self.rec_num - current_num):
        #         self.recommend_list.append(information())

    def recv_from_client(self):     #按规定方式从客户端接收信息，并存入self.info
        self.info.set_database(self.recv())  #调用self.info的成员函数将收到的信息存入database，下同
        self.send(suc_msg)                   #发送成功接收的消息号接收下一个
        print('database: ', self.info.get_database())

        self.info.set_title (self.recv())
        self.send(suc_msg)
        print('title: ', self.info.get_title())

        self.info.set_origin (self.recv())
        self.send(suc_msg)
        print('origin: ', self.info.get_origin())

        self.info.set_cite_number (self.recv())
        self.send(suc_msg)
        print('site_number: ', self.info.get_cite_number())

        self.info.set_date (self.recv())
        self.send(suc_msg)
        print('date: ', self.info.get_date())

        self.info.set_doi (self.recv())
        self.send(suc_msg)
        print('doi: ', self.info.get_doi())

        self.info.set_abstract (self.recv())
        self.send(suc_msg)
        print('abstract: ', self.info.get_abstract())

        for i in range(len_author):  # 个数由作者个数决定
            self.info.set_author (self.recv(),i)
            self.send(suc_msg)
        print('author:', self.info.get_author(i))

        for i in range(len_key):  # 个数由关键词个数决定
            self.info.set_key_word (self.recv(),i)
            self.send(suc_msg)
        print('key_word:', self.info.get_key_word(i))

        for i in range(len_ref):  # 个数由关键词个数决定
            self.info.set_ref (self.recv(),i)
            self.send(suc_msg)
        print('ref:', self.info.get_ref(i))

        for i in range(len_field):
            self.info.set_field(self.recv(),i)
            self.send(suc_msg)
        print('field:', self.info.get_field(i))

    def send_to_client(self, input):  #将输入的input发送给客户端，输入的input是结构化的information对象
        self.send(input.get_database())
        if self.confirm()!=0:
            return -1

        self.send(input.get_title())
        if self.confirm() != 0:
            return -1

        self.send(input.get_origin())
        if self.confirm() != 0:
            return -1

        self.send(input.get_cite_number())
        if self.confirm() != 0:
            return -1

        self.send(input.get_date())
        if self.confirm() != 0:
            return -1

        self.send(input.get_doi())
        if self.confirm() != 0:
            return -1

        self.send(input.get_abstract())
        if self.confirm() != 0:
            return -1

        for i in range(len_author):
            self.send(input.get_author(i))
            if self.confirm() != 0:
                return -1
        for i in range(len_key):
            self.send(input.get_key_word(i))
            if self.confirm() != 0:
                return -1
        for i in range(len_ref):
            self.send(input.get_ref(i))
            if self.confirm() != 0:
                return -1

        for i in range(len_field):
            self.send(input.get_field(i))
            if self.confirm() != 0:
                return -1

        return 0

    def list_to_client(self):
        for j in range(self.rec_num):
            self.send(self.recommend_list[j].get_database())
            if self.confirm() != 0:
                return -1

            self.send(self.recommend_list[j].get_title())
            if self.confirm() != 0:
                return -1

            self.send(self.recommend_list[j].get_origin())
            if self.confirm() != 0:
                return -1

            self.send(self.recommend_list[j].get_cite_number())
            if self.confirm() != 0:
                return -1

            self.send(self.recommend_list[j].get_date())
            if self.confirm() != 0:
                return -1

            self.send(self.recommend_list[j].get_doi())
            if self.confirm() != 0:
                return -1

            self.send(self.recommend_list[j].get_abstract())
            if self.confirm() != 0:
                return -1

            for i in range(len_author):
                self.send(self.recommend_list[j].get_author(i))
                if self.confirm() != 0:
                    return -1
            for i in range(len_key):
                self.send(self.recommend_list[j].get_key_word(i))
                if self.confirm() != 0:
                    return -1
            for i in range(len_ref):
                self.send(self.recommend_list[j].get_ref(i))
                if self.confirm() != 0:
                    return -1

            for i in range(len_field):
                self.send(self.recommend_list[j].get_field(i))
                if self.confirm() != 0:
                    return -1
        return 0

    def weight_from_client(self):
        self.weight.set_database(float(self.recv()))
        self.send(suc_msg)
        print('database: ', self.weight.get_database())

        self.weight.set_author(float(self.recv()))
        self.send(suc_msg)
        print('author: ', self.weight.get_author())

        self.weight.set_key_word(float(self.recv()))
        self.send(suc_msg)
        print('keyword: ', self.weight.get_key_word())

        self.weight.set_origin(float(self.recv()))
        self.send(suc_msg)
        print('origin: ', self.weight.get_origin())

        self.weight.set_ref(float(self.recv()))
        self.send(suc_msg)
        print('reference: ', self.weight.get_ref())

        self.weight.set_field(float(self.recv()))
        self.send(suc_msg)
        print('field: ', self.weight.get_field())

        self.rec_num = int(self.recv())
        self.send(suc_msg)
        print('recommend num: ', self.rec_num)


def send_to_database(info, expe=False):    #提交论文信息至数据库
    if expe:
        tb_str = "sciexp"
    else:
        tb_str = "paperinfo"
    db = pymysql.connect("localhost", "root", "123456", db="scidb", charset='utf8')  # 连接数据库
    cursor = db.cursor()  # 获取数据库操作游标
    sql = "insert" + " into " + tb_str + "(id, db_paper, cite_number, title, author1, author2, author3, author4,  \
        author5, author6, keyword1, keyword2, keyword3, keyword4, keyword5, keyword6, keyword7, source, date, \
        reference1, reference2, reference3, reference4, reference5, reference6, reference7, reference8, reference9,  \
        reference10, doi, abstract, field1, field2, field3 )VALUES(0, '%s','%s','%s','%s','%s','%s','%s','%s','%s','%s', \
        '%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s') " % \
          (info.content['database'], info.content['cite_number'], info.content['title'], info.content['author'][0], \
           info.content['author'][1], info.content['author'][2], info.content['author'][3], info.content['author'][4], \
           info.content['author'][5], info.content['key_word'][0], info.content['key_word'][1], \
           info.content['key_word'][2], info.content['key_word'][3], info.content['key_word'][4], \
           info.content['key_word'][5], info.content['key_word'][6], \
           info.content['origin'], info.content['date'], info.content['ref'][0], info.content['ref'][1], \
           info.content['ref'][2], info.content['ref'][3], info.content['ref'][4], info.content['ref'][5], \
           info.content['ref'][6], info.content['ref'][7], info.content['ref'][8], info.content['ref'][9], \
           info.content['doi'], info.content['abstract'], info.content['field'][0], info.content['field'][1], info.content['field'][2])
    cursor.execute(sql)  # 执行sql语句
    db.commit()  # 提交到数据库执行
    cursor.close()
    db.close()  # 关闭数据库连接


if __name__ == '__main__':
    Server = my_server(ip=socket.gethostbyname(socket.gethostname()))   #使用本机ip地址
    while True:
        Server.conn()  # 等待客户端连接，默认最大数为5
        try:
            quest = Server.recv()                # 确认请求类型，包括’send'纯发送指令，和‘search’搜索相关文档指令
            if quest == 'send':  # 收到发送文章信息
                print(quest, 'quest received')
                Server.send(suc_msg)
                Server.recv_from_client()
                msg = Server.recv()
                if msg == 'finish':
                    print('receive OK!')
                    send_to_database(Server.info, expe)
                    continue
                else:
                    Server.send(err_msg)
                    continue

            elif quest == 'search':  # 搜索请求
                print(quest, 'quest received')
                Server.send(wait_msg)
                Server.recv_from_client()
                print(quest, 'Sent Done')

                Server.recommend(expe)
                for i in range(Server.rec_num):
                    print(Server.recommend_list[i].content)
                Server.send(suc_msg)

                msg = Server.recv()
                if msg == "quest_info":
                    Server.send(suc_msg)
                    Server.list_to_client()

                else:
                    Server.send(err_msg)
                    continue

            elif quest == 'send_weight':
                print(quest, 'quest received')
                Server.send(suc_msg)
                Server.weight_from_client()
                msg = Server.recv()
                if msg == 'finish_weight':
                    print('receive weight OK!')
                    continue
                else:
                    Server.send(err_msg)
                    continue
            else:
                Server.send(err_msg)
                continue
        except ConnectionResetError as e:
            print('connected error')
            break
    Server.close()

