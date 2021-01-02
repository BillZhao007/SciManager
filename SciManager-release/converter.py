from globals import *
from client import *
import os


def send_converter(db_paper, cite_number, title, author1, author2, author3, author4, author5, author6,
                keyword1, keyword2, keyword3, keyword4, keyword5, keyword6, keyword7, source, date,
                reference1, reference2, reference3, reference4, reference5, reference6, reference7, reference8,
                reference9, reference10, doi, abstract, field1, field2, field3,
                addr=socket.gethostbyname(socket.gethostname())):
    inp = information()
    inp.set_database(db_paper)
    inp.set_cite_number(cite_number)
    inp.set_title(title)
    inp.set_author(author1, 0)
    inp.set_author(author2, 1)
    inp.set_author(author3, 2)
    inp.set_author(author4, 3)
    inp.set_author(author5, 4)
    inp.set_author(author6, 5)
    inp.set_key_word(keyword1, 0)
    inp.set_key_word(keyword2, 1)
    inp.set_key_word(keyword3, 2)
    inp.set_key_word(keyword4, 3)
    inp.set_key_word(keyword5, 4)
    inp.set_key_word(keyword6, 5)
    inp.set_key_word(keyword7, 6)
    inp.set_origin(source)
    inp.set_date(date)
    inp.set_ref(reference1, 0)
    inp.set_ref(reference2, 1)
    inp.set_ref(reference3, 2)
    inp.set_ref(reference4, 3)
    inp.set_ref(reference5, 4)
    inp.set_ref(reference6, 5)
    inp.set_ref(reference7, 6)
    inp.set_ref(reference8, 7)
    inp.set_ref(reference9, 8)
    inp.set_ref(reference10, 9)
    inp.set_doi(doi)
    inp.set_abstract(abstract)
    inp.set_field(field1, 0)
    inp.set_field(field2, 1)
    inp.set_field(field3, 2)
    return send_info(addr, inp)


def search_converter(db_paper, cite_number, title, author1, author2, author3, author4, author5, author6,
                     keyword1, keyword2, keyword3, keyword4, keyword5, keyword6, keyword7, source, date,
                     reference1, reference2, reference3, reference4, reference5, reference6, reference7, reference8,
                     reference9, reference10, doi, abstract, field1, field2, field3,
                     wt_db, wt_aut, wt_kw, wt_ori, wt_ref, wt_f, rec_n="5", cache_pth="./cache",
                     addr=socket.gethostbyname(socket.gethostname())):
    inp = information()
    inp.set_database(db_paper)
    inp.set_cite_number(cite_number)
    inp.set_title(title)
    inp.set_author(author1, 0)
    inp.set_author(author2, 1)
    inp.set_author(author3, 2)
    inp.set_author(author4, 3)
    inp.set_author(author5, 4)
    inp.set_author(author6, 5)
    inp.set_key_word(keyword1, 0)
    inp.set_key_word(keyword2, 1)
    inp.set_key_word(keyword3, 2)
    inp.set_key_word(keyword4, 3)
    inp.set_key_word(keyword5, 4)
    inp.set_key_word(keyword6, 5)
    inp.set_key_word(keyword7, 6)
    inp.set_origin(source)
    inp.set_date(date)
    inp.set_ref(reference1, 0)
    inp.set_ref(reference2, 1)
    inp.set_ref(reference3, 2)
    inp.set_ref(reference4, 3)
    inp.set_ref(reference5, 4)
    inp.set_ref(reference6, 5)
    inp.set_ref(reference7, 6)
    inp.set_ref(reference8, 7)
    inp.set_ref(reference9, 8)
    inp.set_ref(reference10, 9)
    inp.set_doi(doi)
    inp.set_abstract(abstract)
    inp.set_field(field1, 0)
    inp.set_field(field2, 1)
    inp.set_field(field3, 2)

    res = send_weight(wt_db, wt_aut, wt_kw, wt_ori, wt_ref, wt_f, rec_num=rec_n, addr=addr)
    if res == -1:
        return -1
    res = search_info(addr=addr, input=inp, rec_n=int(rec_n))
    if res == -1:
        return -1
    if not os.path.exists(cache_pth):
        os.makedirs(cache_pth)
    f = open(cache_pth + "/recommendation.txt", 'w')
    f.close()
    f = open(cache_pth + "/recommendation.txt", 'a')
    for i in range(len(res)):
        print(res[i].content)
        f.write(res[i].tostring() + '\n')
    f.close()
    return 0
