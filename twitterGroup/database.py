import sqlite3
from threading import RLock
import array

class db:
    _sql = 0
    lock = RLock()
    def __init__(self, name):
        self._sql = sqlite3.connect(name)
        self._checkInit()
    def _checkInit(self):
        try:
            self.lock.acquire()
            if self._sql.execute("""select count(*) from sqlite_master where name="list"; """).fetchone() is 0:
                print "need to make database"
                self._sql.execute("create table list(Uname text, Gname text)")
                self._sql.commit()
        finally:
            self.lock.release()
    def join(self, user, group):
        try:
            self.lock.acquire()
            if not self.isIn(user, group):
                do = "insert into list(Uname, Gname) values (?, ?)"
                self._sql.execute(do, (user, group))
                self._sql.commit()
        finally:
            self.lock.release()
    def isIn(self, user, group):
        try:
            self.lock.acquire()
            ret = self._sql.execute("select * from list where Uname = ? and Gname = ?;", (user, group)).fetchall() != []
        finally:
            self.lock.release()
        return ret
