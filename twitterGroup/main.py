import twitter
import database

import os
import ConfigParser
import threading

class handleSending(threading.Thread):
    sentBy = ""
    sentTo = ""
    message = ""
    def run (self):
        pass

class controler:
    account = 0
    data = 0
    def __init__(self, a, d):
        self.account = a
        self.data = d
    def run (self):
        pass


def main ():
    config = ConfigParser.SafeConfigParser()
    config.read('config.cfg')
    
    Account = twitter.Api(username = config.get('user', 'name'), password = config.get('user', 'password'))
 
    Account.PostUpdate('test')

    data = database.db(config.get('file', 'database'))
    data.join('matthewfl', 'something')
    
    C = controler(Account, data)

if __name__ == "__main__":
    main()
