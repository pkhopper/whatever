#!/usr/bin/env python
# coding=utf-8

__author__ = 'liletian'

import os
import sys
import os.path as pathtool
import web


render = web.template.render('templates/')
urls = (
    '/', 'Index',
    '/(.*)/', 'Index',
    '/res/(.*)', 'redirect_static',
)


class redirect:
    def GET(self, path=''):
        web.seeother('/' + path)


class redirect_static:
    def GET(self, path=''):
        web.seeother('/static/' + path)


class Index:
    def GET(self, path=''):
        return "" #web.notfound()


class InternalErr:
    def GET(self, messge=''):
        return web.notfound()


class hellowode:
    def GET(self):
        data = web.input(name='Bob')
        return render.hellowode(data.name)


if __name__ == "__main__":
    app = web.application(urls, globals())
    app.internalerror = web.BadRequest #.debugerror
    app.run()
