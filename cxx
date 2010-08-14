#!/usr/bin/python

import os,sys

True = 1==1
False = 1==0

class cxx:
    def __init__(self, arg, name=None, out=None):
        self.argv = arg
        self.name = name
        self.out = out
    def think(self):
        if self.name == None:
            self.getName()
        if self.out == None:
            self.out = ".cxx.compiled."+self.name.replace("/", "").replace(".", "")
    def getName (self):
        num = 0
        for arg in self.argv:
            if num == 1:
                self.name = arg
                return
            num += 1
    def getFile (self):
        file = open(self.name, "r")
        content = ""
        for l in file:
            if l.find("#!"):
                content += l
        name = ".cxx.source."+self.name.replace("/", "").replace(".", "")
        out = open(name, "w+")
        out.write(content)
        out.close()
        file.close()
        return name
    def compile (self):
        name = self.getFile()
        os.system("g++ -x c++ -Wall \""+name+"\" -o \""+self.out+"\"")
        #os.system("rm \""+name+"\"")
        print "\n"
    def run (self):
        os.system("./"+self.out)
    def getTime (self, name):
        (mode, ino, dev, nlink, uid, gid, size, atime, mtime, ctime) = os.stat(name)
        return ctime
    def checkCompile (self):
        try:
            return self.getTime(self.name) > self.getTime(self.out)
        except:
            return True
    def go (self):
        self.think()
        if self.checkCompile():
            self.compile()
        self.run()



def main():
    Control = cxx(sys.argv)
    Control.go()

if __name__ == "__main__":
    main()
