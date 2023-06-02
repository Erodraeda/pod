from utils.data_request import DataRequest
import time
import os

class Main:
    def __init__(self):
        self.running = False
        self.dataRequest = DataRequest()

    def run(self):
        self.running = True
        print(" ----- \n Welcome to the client side!\n")
        self.menu()

    def start(self):
        while self.running == True:
            # os.system('clear')
            time.sleep(2)

    def menu(self):
        self.exit = False
        while self.exit != True:

            print("Please select what you'd like to do: \n")
            selection = input(" 1 - Get all servers \n 2 - Get a specific server \n 3 - Add a new server \n 4 - Delete a server \n 5 - Update a server's name \n 0 - Exit \n\n ")
            value = ''
            if len(selection) > 0:
                value = int(selection)
            
            if type(value) != int:
                os.system('clear')
                print(" ----- \n Please input a number! \n ----- ")
                time.sleep(2)
            elif value == 0:
                self.exit = True
            elif value == 1:
                os.system('clear')
                arg1 = 'all'
                self.dataRequest.get(arg1)
                time.sleep(2)
            elif value == 2:
                os.system('clear')
                arg1 = input("Please input the server ID you would like to get: ")
                self.dataRequest.get(arg1)
                time.sleep(2)
            elif value == 3:
                os.system('clear')
                arg1 = input("Please input the name of the server you'd like to add: ")
                self.dataRequest.add(arg1)
                time.sleep(2)
            elif value == 4:
                os.system('clear')
                arg1 = input("Please input the server ID you would like to delete: ")
                self.dataRequest.delete(arg1)
                time.sleep(2)
            elif value == 5:
                os.system('clear')
                arg1 = input("Please input the server ID you would like to update: ")
                arg2 = input("Please input the name you'd like to set to that server: ")
                self.dataRequest.update(arg1, arg2)
                time.sleep(2)
            elif value > 5:
                os.system('clear')
                print(" ----- \n Please input a valid number! \n ----- ")
                time.sleep(2)
            else:
                os.system('clear')
                print(" ----- \n Please input a number! \n ----- ")
                time.sleep(2)

            
            

if __name__ == "__main__":
    main = Main()
    main.run()