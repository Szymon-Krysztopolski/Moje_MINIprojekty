import pyautogui
import keyboard
import time
import os
from constants import *

Options = []

Loops = 5
DelayBeforeSpam = 5
DelayAfterWord = 0.2
FileName = "spam.txt"
FileNameManualSpam = "manual.txt"


def menu() -> str:
    os.system("cls")
    print("choose option:")
    print("---------------------------")
    print("1. fastSpam")
    print("2. manualSpam")
    print("3. change settings")
    print("4. show settings")
    print("5. reset program")
    print("e. EXIT")
    print("---------------------------")
    return input("your decision: ")


def getLoops() -> int:
    return Loops


def getDelayAfterWord() -> float:
    return DelayAfterWord


def fastSpam(loops: int, delay: int) -> None:
    time.sleep(DelayBeforeSpam)
    file = open(PATH_FILES + FileName, "r").readlines()

    [[writeFromKeyboard(word, delay) for word in file] for _ in range(loops)]


def writeFromKeyboard(word: str, delay: int) -> None:
    # pyautogui.keyDown("ctrl")
    # pyautogui.press("a")
    # pyautogui.press("backspace")
    # pyautogui.keyUp("ctrl")

    pyautogui.typewrite(word)
    pyautogui.press("enter")
    time.sleep(delay)


def settingShow() -> None:
    print("---------------------------")
    for mess in Options:
        print(mess)
    print("---------------------------")
    input("Press Enter to continue...")


def settingChange() -> None:
    global Loops, DelayBeforeSpam, DelayAfterWord, FileName, FileNameManualSpam
    addon = 1
    print("---------------------------")
    for mess in Options:
        print(str(addon)+". "+mess)
        addon += 1
    print("e. Exit")
    print("---------------------------")

    match input("your decision: "):
        case '1':
            value = int(input("new value of variable: "))
            if LOOP_MIN_VALUE <= value <= LOOP_MAX_VALUE:
                Loops = value
            else:
                print(
                    f"Error with value --- min: {LOOP_MIN_VALUE}, max: {LOOP_MAX_VALUE}!")
        case '2':
            value = int(input("new value of variable: "))
            if SPAM_DELAY_MIN_VALUE <= value <= SPAM_DELAY_MAX_VALUE:
                DelayBeforeSpam = value
            else:
                print(
                    f"Error with value --- min: {SPAM_DELAY_MIN_VALUE}, max: {SPAM_DELAY_MAX_VALUE}!")
        case '3':
            value = float(input("new value of variable: "))
            if WORD_DELAY_MIN_VALUE <= value <= WORD_DELAY_MAX_VALUE:
                DelayAfterWord = value
            else:
                print(
                    f"Error with value --- min: {WORD_DELAY_MIN_VALUE}, max: {WORD_DELAY_MAX_VALUE}!")
        case '4':
            FileName = str(input("new value of variable: "))
        case '5':
            FileNameManualSpam = str(input("new value of variable: "))
        case 'e':
            return
    refreshOprions()
    input("Press Enter to continue...")


def hardReset() -> None:
    global Loops, DelayBeforeSpam, DelayAfterWord, FileName

    Loops = 5
    DelayBeforeSpam = 5
    DelayAfterWord = 0.2
    FileName = "spam.txt"
    refreshOprions()

    print("done")
    input("Press Enter to continue...")


def refreshOprions() -> None:
    global Options

    Options = [f"loops of fastSpam: {Loops}",
               f"delay before fastSpam: {DelayBeforeSpam}",
               f"delay after word in fastSpam: {DelayAfterWord}",
               f"file used for fastSpam: {FileName}",
               f"file used for manualSpam: {FileNameManualSpam}"
               ]


def manualSpam() -> None:
    print("space. \tSPAM")
    print("e. \tEXIT")
    while True:
        if keyboard.is_pressed(" "):
            writeFromKeyboard(
                open(PATH_FILES + FileNameManualSpam, 'r').read(), 0)
            # time.sleep(WORD_DELAY_MIN_VALUE)
        elif keyboard.is_pressed("e"):
            break
