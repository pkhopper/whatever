#!/usr/bin/env python
# coding=utf-8

__author__ = 'pkhopper'

import web
from web import form


render = web.template.render('templates/', base='layout')
urls = (
    # '/(.*)/', 'Index',
    '/res/(.*)', 'redirect_static',
    # pages
    '/', 'PageIndex',
    '/login', 'PageLogin',
    '/logout', 'PageLogout',
    '/query', 'PageQuery',
    '/status', 'PageStatus',
    '/viewlog', 'PageViewLog',
    '/data', 'PageData',
)


allowed = (
    ('aaa', '123123'),
)


web.config.debug = False
app = web.application(urls, globals())
app.internalerror = web.BadRequest #.debugerror
session = web.session.Session(app, web.session.DiskStore('sessions'))


# default act
class redirect:
    def GET(self, path=''):
        web.seeother('/' + path)


class redirect_static:
    def GET(self, path=''):
        web.seeother('/static/' + path)


class InternalErr:
    def GET(self, messge=''):
        return web.notfound()


# pages
class PageIndex:
    def GET(self, path=None):
        if not session.logged_in:
            raise web.seeother('/login')
        return render.PageIndex()


class PageLogin:
    def GET(self):
        return render.PageLogin()

    def POST(self):
        i = web.input()
        username = i.get('username')
        passwd = i.get('passwd')
        if (username, passwd) in allowed:
            session.logged_in = True
            web.setcookie('system_mangement', '', 60)
            return web.seeother('/')
        else:
            return web.seeother("/login")


class PageLogout:
    def GET(self):
        session.logged_in = False
        return web.seeother("/login")


class PageQuery:
    def GET(self):
        if not session.logged_in:
            return web.seeother('/')
        return render.PageQuery()
    # def GET(self, path):
    #     data = web.input(path="")
    #     return render.PageQuery(data)


class PageStatus:
    def GET(self):
        if not session.logged_in:
            return web.seeother('/')
        return render.PageStatus()


class PageViewLog:
    def GET(self):
        if not session.logged_in:
            return web.seeother('/')
        return web.seeother('/static/log/')
        # return render.PageViewLog()


class PageData:
    def GET(self):
        if not session.logged_in:
            return web.seeother('/')
        return web.seeother('/static/db/')
        # return render.PageViewLog()



if __name__ == "__main__":
    app.run()
