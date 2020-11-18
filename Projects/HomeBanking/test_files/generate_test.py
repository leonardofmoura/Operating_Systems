import random

def main():
    testFile = open("test.sh",'a')

    userNumber = 1500
    userPass = "top_secret"
    adminPass = "admiiiiiiiin"

    createUser(testFile,userNumber,adminPass,userPass)
    checkUserBalance(testFile,userNumber,userPass)
    transferRandomAccounts(testFile,userNumber,userPass)
    checkUserBalance(testFile,userNumber,userPass)
    serverShutdown(testFile,adminPass)
    checkUserBalance(testFile,userNumber,userPass)

    testFile.close()

    return

#assumes testFile is open
def createUser(testFile,userNumber,adminPass,userPass):
    for userID in range(userNumber):
        balance = random.randint(50,10000)
        testFile.write("./user 0 \"%s\" 10 0 \"%d %d %s\" &\n" % (adminPass,userID,balance,userPass))
    
    return

#assumes testFile is open
def checkUserBalance(testFile,userNumber,userPass):
    for userID in range(userNumber):
        testFile.write("./user %d \"%s\" 10 1 \"\" &\n" % (userID,userPass))

    return

def transferRandomAccounts(testFile,userNumber,userPass):
    for userID in range(userNumber):
        transferAmmount = random.randint(1,50)
        destination = random.randint(1,50)
        testFile.write("./user %d \"%s\" 10 2 \"%d %s\" &\n"% (userID,userPass,destination,transferAmmount))

    return

def serverShutdown(testFile,adminPass):
    testFile.write("./user 0 \"%s\" 10 3 \"\" \n" % (adminPass))

    return

if __name__== "__main__":
  main()
