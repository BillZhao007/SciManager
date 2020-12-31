# Parameters
null='&'
len_author = 6
len_key = 7
len_field = 3
len_ref = 10
suc_msg = 'OK'
err_msg = 'error'
wait_msg = 'wait'
break_time = 60.

# Info Storage Structure
class information():
    def __init__(self):
        self.content = {'database':null, 'cite_number':null,'title':null,'author':[null for i in range(len_author)],
                     'key_word':[null for i in range(len_key)],'origin':null,'date':null,
                     'ref':[null for i in range(len_ref)],'doi':null,'abstract':null,
                     'field':[null for i in range(len_field)]}
    def get_info(self):  # Return All Info
        return self.content
    def get_database(self):
        return self.content['database']
    def get_cite_number(self):
        return self.content['cite_number']
    def get_title(self):
        return self.content['title']
    def get_author(self,index):  # Return Single Author
        return self.content['author'][index]
    def get_key_word(self,index):
        return self.content['key_word'][index]
    def get_origin(self):
        return self.content['origin']
    def get_ref(self,index):
        return self.content['ref'][index]
    def get_doi(self):
        return self.content['doi']
    def get_date(self):
        return self.content['date']
    def get_abstract(self):
        return self.content['abstract']
    def get_field(self, index):
        return self.content['field'][index]

    def set_database(self,database):  # Input of String
        self.content['database'] = database
    def set_cite_number(self,cite_number):
        self.content['cite_number'] = cite_number
    def set_title(self,title):
        self.content['title'] = title
    def set_date(self,date):
        self.content['date'] = date
    def set_author(self,author,index):
        if index in range(len_author):
            self.content['author'][index]=author
    def set_key_word(self,key_word,index):
        if index in range(len_key):
            self.content['key_word'][index] = key_word
    def set_origin(self,origin):
        self.content['origin'] = origin
    def set_ref(self,ref,index):
        if index in range(len_ref):
            self.content['ref'][index] = ref
    def set_doi(self, doi):
        self.content['doi'] = doi
    def set_abstract(self, abstract):
        self.content['abstract'] = abstract
    def set_field(self, field, index):
        if index in range(len_field):
            self.content['field'][index] = field

    def copy(self, info):
        self.content['database'] = info.content['database']
        self.content['cite_number'] = info.content['cite_number']
        self.content['title'] = info.content['title']
        self.content['date'] = info.content['date']
        for index in range(len_author):
            self.content['author'][index] = info.content['author'][index]
        for index in range(len_key):
            self.content['key_word'][index] = info.content['key_word'][index]
        self.content['origin'] = info.content['origin']
        for index in range(len_ref):
            self.content['ref'][index] = info.content['ref'][index]
        self.content['doi'] = info.content['doi']
        self.content['abstract'] = info.content['abstract']
        for index in range(len_field):
            self.content['field'][index] = info.content['field'][index]

    def tostring(self):
        res = self.content['database'] + '|' + self.content['cite_number'] + '|' + self.content['title']
        for i in range(len_author):
            res += '|' + self.content['author'][i]
        for i in range(len_key):
            res += '|' + self.content['key_word'][i]
        res += '|' + self.content['origin'] + '|' + self.content['date']
        for i in range(len_ref):
            res += '|' + self.content['ref'][i]
        res += '|' + self.content['doi']
        for i in range(len_field):
            res += '|' + self.content['field'][i]
        return res


class weight():
    def __init__(self):
        self.content = {"author":0., "key_word":0., "origin":0., "ref":0., "field":0., "database":0.}
    def get_info(self):  # Return All Info
        return self.content
    def get_database(self):
        return self.content['database']
    def get_author(self):
        return self.content['author']
    def get_key_word(self):
        return self.content['key_word']
    def get_origin(self):
        return self.content['origin']
    def get_ref(self):
        return self.content['ref']
    def get_field(self):
        return self.content['field']

    def set_database(self,database):  # Input of String
        self.content['database'] = database
    def set_author(self,author):
        self.content['author']=author
    def set_key_word(self,key_word):
        self.content['key_word'] = key_word
    def set_origin(self,origin):
        self.content['origin'] = origin
    def set_ref(self,ref):
        self.content['ref'] = ref
    def set_field(self, field):
        self.content['field'] = field


def correlation(info1, info2, wt):
    if info1.content['title'] == info2.content['title'] and info1.content['date'] == info2.content['date']:
        return -1
    score = 0.
    if info1.content['database'] == info2.content['database']:
        score = wt.content['database']
    if info1.content['origin'] == info2.content['origin']:
        score += wt.content['origin']
    for i in range(len_author):
        for j in range(len_author):
            tmp1 = info1.content["author"][i]
            tmp2 = info2.content["author"][j]
            if tmp1 == null or tmp2 == null:
                break
            elif tmp1 == tmp2:
                score += wt.content['author']
                break
    for i in range(len_key):
        for j in range(len_key):
            tmp1 = info1.content["key_word"][i]
            tmp2 = info2.content["key_word"][j]
            if tmp1 == null or tmp2 == null:
                break
            elif tmp1 == tmp2:
                score += wt.content['key_word']
                break
    for i in range(len_field):
        for j in range(len_field):
            tmp1 = info1.content["field"][i]
            tmp2 = info2.content["field"][j]
            if tmp1 == null or tmp2 == null:
                break
            elif tmp1 == tmp2:
                score += wt.content['field']
                break
    for i in range(len_ref):
        for j in range(len_ref):
            tmp1 = info1.content["ref"][i]
            tmp2 = info2.content["ref"][j]
            if tmp1 == null or tmp2 == null:
                break
            elif tmp1 == tmp2 or tmp2 == info1.content['title'] or tmp1 == info2.content['title']:
                score += wt.content['ref']
                break
    return score
