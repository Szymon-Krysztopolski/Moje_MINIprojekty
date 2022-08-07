from functions import *


def main():
    refreshOprions()
    while True:
        match menu():
            case '1':
                fastSpam(getLoops(), getDelayAfterWord())
            case '2':
                manualSpam()
            case '3':
                settingChange()
            case '4':
                settingShow()
            case '5':
                hardReset()
            case 'e':
                exit("Program ends...")


if __name__ == '__main__':
    main()
