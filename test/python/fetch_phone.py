#!/usr/bin/python2.7
#coding=utf-8

import os
import sys
import urllib
import re
import time
import random

class FetchImage:
    def __init__(self):
        self.url_entry = 'http://bj.58.com/fushi/pn%s/'
        self.count = 1

    def get_image(self):
        for page_id in range(1, 21):
            page_url = self.url_entry % str(page_id)
            page_content = urllib.urlopen(page_url).read()
            all_matches = re.findall('<a href="(http://bj.58.com/fushi/.*.shtml)" target="_blank"', page_content)
            for one_url in all_matches:
                #print '@'*10, one_url
                one_content = urllib.urlopen(one_url).read()
                phone_urls = re.findall('\'(http://image.58.com/showphone.aspx?[\s\S]+?)\'', one_content)
                for each_phone_url in phone_urls:
                    #print '#'*10, each_phone_url
                    image_content = urllib.urlopen(each_phone_url).read()
                    image_content_save_path = 'images2/' + str(self.count) + '.gif'
                    self.count += 1
                    write_file = open(image_content_save_path, 'wb')
                    write_file.write(image_content)
                    write_file.close()
                    sleep_time = 1 + 1 * random.random()
                    time.sleep(sleep_time)

if __name__ ==  '__main__':
    fi = FetchImage()
    fi.get_image()
