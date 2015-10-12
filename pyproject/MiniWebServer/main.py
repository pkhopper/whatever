#!/usr/bin/env python
# coding=utf-8

__author__ = 'liletian'

import os
import sys
import os.path as pathtool
import web

render = web.template.render('templates/')

urls = (
    '/(.*)/', 'redirect',
    '/', 'index',
    '/hello', 'hellowode',
    '/h5', 'test_h5',
)


# http://webpy.org/cookbook/helloworld
class redirect:
    def GET(self, path):
        web.seeother('/' + path)

class index:
    def GET(self):
        return "this is index page"


class hellowode:
    def GET(self):
        data = web.input(name='Bob')
        return render.hellowode(data.name)


app = web.application(urls, globals())


if __name__ == "__main__":
    app.run()


