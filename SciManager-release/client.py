import socket
import time
from globals import *


class my_client():
    def __init__(self, rec_n=5):
        self.client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.info = information()
        self.rec_n = rec_n
        self.list = list()
        # for i in range(rec_n):
        #     self.list += [information()]
    def conn(self,ip,port=8888):
        self.client.connect((ip, port))
    def disconn(self):
        self.client.close()

    def send(self, msg):
        self.client.send(msg.encode('utf-8'))
    def recv(self, buffer=1024):
         return self.client.recv(buffer).decode('utf-8')
    def confirm(self):
        tmp = self.recv()
        if tmp == 'OK':
            return 0
        elif tmp == 'error':
            return 1
        elif tmp == 'wait':
            return 2
        else:
            return -1

    def send_to_server(self, input):  # 将input发送给服务器，input为information类的对象
        self.send(input.get_database())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        self.send(input.get_title())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        self.send(input.get_origin())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        self.send(input.get_cite_number())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        self.send(input.get_date())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        self.send(input.get_doi())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        self.send(input.get_abstract())
        if self.confirm() != 0 and self.confirm() != 2:
            return -1

        for i in range(len_author):
            self.send(input.get_author(i))
            if self.confirm() != 0 and self.confirm() != 2:
                return -1
        for i in range(len_key):
            self.send(input.get_key_word(i))
            if self.confirm() != 0 and self.confirm() != 2:
                return -1
        for i in range(len_ref):
            self.send(input.get_ref(i))
            if self.confirm() != 0 and self.confirm() != 2:
                return -1

        for i in range(len_field):
            self.send(input.get_field(i))
            if self.confirm() != 0 and self.confirm() != 2:
                return -1
        return 0

    def recv_from_server(self):  # 接收后存储在self.info
        # i = 0
        self.info.set_database(self.recv())  # 调用self.info的成员函数将收到的信息存入database，下同
        self.send(suc_msg)  # 发送成功接收的消息号接收下一个
        print('database: ', self.info.get_database())

        self.info.set_title(self.recv())
        self.send(suc_msg)
        print('title: ', self.info.get_title())

        self.info.set_origin(self.recv())
        self.send(suc_msg)
        print('origin: ', self.info.get_origin())

        self.info.set_cite_number(self.recv())
        self.send(suc_msg)
        print('site_number: ', self.info.get_cite_number())

        self.info.set_date(self.recv())
        self.send(suc_msg)
        print('date: ', self.info.get_date())

        self.info.set_doi(self.recv())
        self.send(suc_msg)
        print('doi: ', self.info.get_doi())

        self.info.set_abstract(self.recv())
        self.send(suc_msg)
        print('abstract: ', self.info.get_abstract())

        for i in range(len_author):  # 个数由作者个数决定
            self.info.set_author(self.recv(), i)
            self.send(suc_msg)
        print('author:', self.info.get_author(i))

        for i in range(len_key):  # 个数由关键词个数决定
            self.info.set_key_word(self.recv(), i)
            self.send(suc_msg)
        print('key_word:', self.info.get_key_word(i))

        for i in range(len_ref):  # 个数由关键词个数决定
            self.info.set_ref(self.recv(), i)
            self.send(suc_msg)
        print('ref:', self.info.get_ref(i))

        for i in range(len_field):
            self.info.set_field(self.recv(), i)
            self.send(suc_msg)
        print('field:', self.info.get_field(i))

    def list_from_server(self):

        for j in range(self.rec_n):
            self.list.append(information())

            self.list[j].set_database(self.recv())  # 调用self.info的成员函数将收到的信息存入database，下同
            self.send(suc_msg)  # 发送成功接收的消息号接收下一个
            print('database: ', self.info.get_database())

            self.list[j].set_title(self.recv())
            self.send(suc_msg)
            print('title: ', self.info.get_title())

            self.list[j].set_origin(self.recv())
            self.send(suc_msg)
            print('origin: ', self.info.get_origin())

            self.list[j].set_cite_number(self.recv())
            self.send(suc_msg)
            print('site_number: ', self.info.get_cite_number())

            self.list[j].set_date(self.recv())
            self.send(suc_msg)
            print('date: ', self.info.get_date())

            self.list[j].set_doi(self.recv())
            self.send(suc_msg)
            print('doi: ', self.info.get_doi())

            self.list[j].set_abstract(self.recv())
            self.send(suc_msg)
            print('abstract: ', self.info.get_abstract())

            for i in range(len_author):  # 个数由作者个数决定
                self.list[j].set_author(self.recv(), i)
                self.send(suc_msg)
            print('author:', self.info.get_author(i))

            for i in range(len_key):  # 个数由关键词个数决定
                self.list[j].set_key_word(self.recv(), i)
                self.send(suc_msg)
            print('key_word:', self.info.get_key_word(i))

            for i in range(len_ref):  # 个数由关键词个数决定
                self.list[j].set_ref(self.recv(), i)
                self.send(suc_msg)
            print('ref:', self.info.get_ref(i))

            for i in range(len_field):
                self.list[j].set_field(self.recv(), i)
                self.send(suc_msg)
            print('field:', self.info.get_field(i))

    def weight_to_server(self, database, author, keyword, origin, ref, field, rec_num="5"):
        self.send(database)
        if self.confirm() != 0:
            print("Weight DB Sent Error")
            return -1

        self.send(author)
        if self.confirm() != 0:
            print("Weight Aut Sent Error")
            return -1

        self.send(keyword)
        if self.confirm() != 0:
            print("Weight KW Sent Error")
            return -1

        self.send(origin)
        if self.confirm() != 0:
            print("Weight Ori Sent Error")
            return -1

        self.send(ref)
        if self.confirm() != 0:
            print("Weight Ref Sent Error")
            return -1

        self.send(field)
        if self.confirm() != 0:
            print("Weight Field Sent Error")
            return -1

        self.send(rec_num)
        if self.confirm() != 0:
            print("Weight RN Sent Error")
            return -1
        return 0


def send_info(addr, input):  # 向服务器发送input中存储的此文献信息，注意不是成员函数，为了调用方便;addr为服务器ip地址
    msg = 'send'  # 标识是发送指令而非搜索相似文献指令
    clt = my_client()    # 实例化
    clt.conn(addr)
    clt.send(msg)
    if clt.confirm() != 0:
        print("Unconfirmed Connection")
        return -1
    if clt.send_to_server(input) != 0:  # 发送异常
        print("Send to Server Error")
        return -1
    msg = 'finish'
    clt.send(msg)
    clt.disconn()
    del clt
    return 0


def send_weight(database, author, keyword, origin, ref, field, rec_num="5", addr=socket.gethostbyname(socket.gethostname())):
    msg = "send_weight"
    clt = my_client(int(rec_num))  # 实例化
    clt.conn(addr)
    clt.send(msg)
    if clt.confirm() != 0:
        print("Unconfirmed Connection in Weight")
        return -1
    if clt.weight_to_server(database, author, keyword, origin, ref, field, rec_num) != 0:  # 发送异常
        print("Weight Sent Error")
        return -1
    msg = 'finish_weight'
    clt.send(msg)
    clt.disconn()
    del clt
    return 0


def search_info(addr, input, rec_n=5):   # 搜索相似文献,output为写入的位置
    msg = 'search'  # 标识是发送指令而非搜索相似文献指令
    result = list()
    clt = my_client(rec_n)  # 实例化
    clt.conn(addr)
    clt.send(msg)
    confirm = clt.confirm()
    if confirm != 0 and confirm != 2:
        return -1
    if clt.send_to_server(input) != 0:  # 发送异常
        print("Search Sent Error")
        return -1
    print("Search Sent Success")
    if confirm == 2:
        time.sleep(2)
        confirm = clt.confirm()
    if confirm != 0:
        return -1

    msg = "quest_info"
    clt.send(msg)
    if clt.confirm() != 0:
        return -1
    clt.list_from_server()
    result = clt.list
    clt.disconn()
    del clt
    for i in range(len(result)):
        print(result[i].content)
    return result


if __name__ =='__main__':    #一个小测试
    info = information()
    info.set_database('unknown database')
    info.set_title('This is title')
    info.set_cite_number('999')
    info.content['author']=['Alpha','Beta','Gamma','Delta','Epsilon','Omega']
    info.content['key_word']=['key_word1','kw2','3','4','5','6','7']
    info.content['field'] = ['field1','field2','field3']
    info.set_origin('origin unknown')
    info.set_date('I am date')
    for i in range(len_ref):
        info.set_ref('reference'+str(i), i)
    info.set_doi('www.xxx.com')
    info.set_abstract('I have nothing to talk about.')

    wt = weight()
    wt.set_database(10)
    wt.set_author(20)
    wt.set_key_word(30)
    wt.set_origin(40)
    wt.set_ref(50)
    wt.set_field(60)

    send_info(addr=socket.gethostbyname(socket.gethostname()), input=info)
    send_weight("10", "20", "30", "40", "50", "60", "5")
    a = search_info(addr=socket.gethostbyname(socket.gethostname()), input=info)
