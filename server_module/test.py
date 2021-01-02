import unittest
import random
from client import *
from server import *


def random_str(randomlength=10):
    random_str = ''
    base_str = 'ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz0123456789'
    length = len(base_str) - 1
    for i in range(randomlength):
        random_str += base_str[random.randint(0, length)]
    return random_str

class test_communication(unittest.TestCase):
    def setUp(self):
        self.info = information()
        self.info.set_database  (random_str(50))
        self.info.set_title (random_str(20))
        for i in range(len_author):
            self.info.set_author(random_str(10),i)
        for i in range(len_key):
            self.info.set_key_word(random_str(5), i)
        self.info.set_date (random_str(4))
        self.info.set_cite_number(random_str(4))
        self.info.set_origin(random_str(50))
        for i in range(len_ref):
            self.info.set_ref(random_str(80),i)
        self.info.set_doi (random_str(30))
        self.info.set_abstract (random_str(1000))
        for i in range(len_field):
            self.info.set_field(random_str(10),i)

    def test_upload(self):
        clt = my_client()
        clt.conn(ip=socket.gethostbyname(socket.gethostname()))  # 暂时连自己的ip建的服务器
        self.assertEqual(0, clt.send_info(self.info))   #正常发送
        clt.disconn()


    def test_search(self):
        clt = my_client()
        clt.conn(ip=socket.gethostbyname(socket.gethostname()))  # 暂时连自己的ip建的服务器
        self.assertEqual(self.info,clt.search_info(self.info))  #正常查找
        clt.disconn()


if __name__== '__main__':
    unittest.main()
