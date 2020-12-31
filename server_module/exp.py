#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pymysql
from server import *

# Server = my_server(ip=socket.gethostbyname(socket.gethostname()))
# info = information()
# info.set_database('unknown database')
# info.set_title('This is title')
# info.set_cite_number('999')
# info.content['author']=['Alpha','Beta','Gamma','Delta','Epsilon','Omega']
# info.content['key_word']=['key_word1','2','3','4','5','6','7']
# info.content['field'] = ['field1','field2','field3']
# info.set_origin('origin unknown')
# info.set_date('I am date')
# for i in range(len_ref):
#     info.set_ref('reference'+str(i), i)
# info.set_doi('www.xxx.com')
# info.set_abstract('I have nothing to talk about.')
#
# wt = weight()
# wt.set_database(10)
# wt.set_author(20)
# wt.set_key_word(30)
# wt.set_origin(40)
# wt.set_ref(50)
# wt.set_field(60)
#
# Server.info = info
# Server.weight = wt
# Server.rec_num = 5
# Server.recommend(True)
# for i in Server.recommend_list:
#     print(i.content)

f = open("./exp.txt", 'w')
f.close()
f = open("./exp.txt", 'a')
f.write("abcd" + '\n')
f.write("efgh")
f.close()
