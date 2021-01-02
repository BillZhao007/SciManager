import requests
import time
from bs4 import BeautifulSoup
import os
import random
import json

requests.adapters.DEFAULT_RETRIES = 5
s = requests.session()
s.keep_alive = False

def get_one_page(url):
    response = requests.get(url)
    # print(response.status_code)
    while response.status_code == 403:
        time.sleep(50 + random.uniform(0, 500))
        response = requests.get(url)
        print(response.status_code)
    # print(response.status_code)
    if response.status_code == 200:
        return response

    return None


def download(title, save_path=None, web='arxiv'):
#    print(title)
#    print(save_path)
    if save_path is None:
        save_path = os.getcwd()
    title_split = title.split()
    if web == 'arxiv':
        url = 'https://arxiv.org/search/?query='
        for str in title_split:
            if str[-1] == ':':
                url = url + str[0:-1] + '%3A' + '+'
            elif str[-1] == ',':
                url = url + str[0:-1] + '%2C' + '+'
            elif str[-1] == '?':
                url = url + str[0:-1] + '%3F' + '+'
            elif str[-1] == '+':
                url = url + str[0:-1] + '%2B' + '+'
            else:
                url = url + str + '+'
        url = url[0:-1] + '&searchtype=title&abstracts=hide&order=&size=50'
        # url = 'https://arxiv.org/search/?query=SOLO%3A+Segmenting%2C+Objects+by+Locations&searchtype=title&abstracts=hide&order=&size=50'

        try:
            # html = requests.get(url)
            html = get_one_page(url)
            soup = BeautifulSoup(html.text, 'html.parser')
            data = soup.select('#main-container > div.content > ol > li > div > p > span > a')
            if len(data) > 0:
                data = data[0]
                link = data.get('href')

                if not os.path.exists(save_path):
                    os.makedirs(save_path)

                pdf = requests.get(link)
                pdf_name = title.replace(': ', '_')
                pdf_root = os.path.join(save_path, pdf_name)
                with open(pdf_root + '.pdf', 'wb') as file:
                    file.write(pdf.content)
                print("download " + title + " successfully")

            else:
                print("document:" + title + " not found")

            html.close()
            time.sleep(1)
        except requests.exceptions.RequestException as e:
            print(e)


def get_arxiv_id(title):
    title_split = title.split()
    url = 'https://arxiv.org/search/?query='
    for str in title_split:
        if str[-1] == ':':
            url = url + str[0:-1] + '%3A' + '+'
        elif str[-1] == ',':
            url = url + str[0:-1] + '%2C' + '+'
        elif str[-1] == '?':
            url = url + str[0:-1] + '%3F' + '+'
        elif str[-1] == '+':
            url = url + str[0:-1] + '%2B' + '+'
        else:
            url = url + str + '+'
    url = url[0:-1] + '&searchtype=title&abstracts=hide&order=&size=50'
    try:
        html = get_one_page(url)
        soup = BeautifulSoup(html.text, 'html.parser')
        data = soup.select('#main-container > div.content > ol > li > div > p > a')
        arxiv_id = None
        if len(data) > 0:
            data = data[0]
            link = data.get('href')
            arxiv_id = link[22:]
        html.close()
        time.sleep(1)
        return arxiv_id
    except requests.exceptions.RequestException as e:
        print(e)


def get_info(title, cache_root):
#    print(title)
    arxiv_id = get_arxiv_id(title)
    if arxiv_id is None:
        print('no information found')
    else:
        url = 'https://api.semanticscholar.org/v1/paper/arXiv:' + arxiv_id
        # html = get_one_page(url)
        # soup = BeautifulSoup(html.text, 'lxml')
        # data = json.loads(soup.read())
        data = requests.get(url)
        data = data.json()
        # abstract = data['abstract']
        # field = data['fieldsOfStudy']
        # year = data['year']
        # venue = data['venue']
        # author = []
        # for i in data['authors']:
        #     author.append(i['name'])
        # topic = []
        # for i in data['topics']:
        #     topic.append(i['topic'])
        # return title, abstract, author, field, year, venue, topic
        file_name = title + '.json'
        file_name = os.path.join(cache_root, file_name)
        with open(file_name, 'w') as f:
            json.dump(data, f)
        print("save json file successfully")





if __name__ == '__main__':
    title = 'Optimal Multi-Object Segmentation with Novel Gradient Vector Flow Based Shape Priors'
    # path = os.getcwd()
    # download(title, path)
    # arxiv_id = get_arxiv_id(title)
    cache_root = os.getcwd()
    get_info(title, cache_root)
