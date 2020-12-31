from pdfminer.high_level import extract_text

def get_title(file_name):
    with open(file_name, 'rb') as fin:
        result = extract_text(fin)
        data = result.split('\nv\ni\nX\nr\na\n\n')  # split text
        num_list = ['1', '2', '3', '4', '5', '6', '7', '8', '9','0']
        if data[0][0] in num_list:
            data = data[1].split('\n\n')  # split title and author
            title = data[0].replace('\n', ' ')
        else:
            data = data[0].split('\n\n')  # split title and author
            title = data[0].replace('\n', ' ')

    return title


if __name__ == '__main__':
    # text_path = "Articulation-aware Canonical Surface Mapping.pdf"
    # text_path = "1708.04811.pdf"
    text_path = '2003.10152.pdf'
    title = get_title(text_path)