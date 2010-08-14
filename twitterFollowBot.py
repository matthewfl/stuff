import twitter
import time

# I think it is 100 call per hour

def main():
    twit = twitter.Api(username="matthewfl", password="itisme")
    twit.SetCache(None)
    while 1:
        g = twit.getPublicTimeline()
        for u in g:
            twit.CreateFrindship(u.user.id)
        time.sleep(240) # should not be less than 10 sec

if __name__ == "__main__":
    main()
