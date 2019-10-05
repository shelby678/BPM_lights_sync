#Author: Shelby Ferrier
#Created: May 2017

import requests
import json
import numbers
import serial
import time

# function golights: sends the Arduino the bpm.
def golights(var_bpm):
    # note that the serial port will vary.
    ser = serial.Serial("/dev/cu.usbmodem1411", 9600)
    time.sleep(3)
    for a in str(var_bpm):
        ser.write(str.encode(a))
        time.sleep(.1)
    ser.close

print("I'm going to sync some lights to your music for you\n"),
print("Just input the song name and the artist name and play the song\n"),

# will repeat if there is an error in finding the BPM or in connecting
# to the Arduino
while True:
    correct = 0
    song_input = input("Enter the song name here: \n")
    artist_input = input("Enter the aritst name here: \n")
    print("""searching for {} by {}
    ...
    ...
    ...""".format(song_input, artist_input))

    # gets the data from the bpm website
    response = requests.get("""https://api.getsongbpm.com/search/?api_key=56a94ebcd4e7011855a8fc430dfac493&type=both&lookup=song:""" + song_input + "+artist:" + artist_input)
    json_data = json.loads(response.text)

    # tries to find a bpm for the given search query
    try:
        count = 0
        while json_data["search"][count]["tempo"] is None:
            count += 1
        print("Setting the lights to {} bpm for {} by {}...".format(
        json_data["search"][count]["tempo"],json_data["search"][count]["song_title"],json_data["search"][count]["artist"]["name"]))
        bpm = json_data["search"][count]["tempo"]

        #tries to connect to the arduino
        try:
            golights(bpm)
        except:
            print("""Couldn't connect to the arduino.
Is it connected to the USB port on the right side of the computer?
Please try again.
""")
            continue

    # if no tempo at all can be found for a given search, prompts another search
    except:
        print ("Nothing turned up for what you searched. Please try again.")
        continue
    command = input("""If you'd like to see all results type "more",
    If you'd like to do a whole new search altogether type "search" \n""")
    count = 0
    while command.lower() not in ['more', 'search']:
        command = input(""" Enter "more" to see all results for your querie,
        or enter "search" to search again.""")
    if command.lower() in ['search']:
        continue

    # if multiple BPM found, asks the user to pick the one they want
    if command.lower() in ['more']:
        list_count = 0
        number_count = 1
        # prints
        for results in json_data['search']:
            if json_data["search"][list_count]["tempo"] is not None:
                print("{}) {} by {} with a bpm of {}".format((number_count
                ), json_data["search"][list_count]["song_title"], json_data
                ["search"][list_count]["artist"]["name"], json_data["search"]
                [list_count]["tempo"]))
                number_count += 1
            list_count += 1

        # prompts the user to search again or to pick their song by index
        song_number = 0
        while song_number not in ['search']:
            song_number = input("""Please enter the number of the song you would like to select, or enter "search" to start a new search.""")
            if song_number in ['search']:
                break
            else:
                try:
                    song_number = int(song_number)
                    if 0 < song_number < count + 1:
                        bpm = json_data["search"][song_number - 1]["tempo"]
                        golights(bpm)
                        break

                    # if the input was out of range, prompts user again
                    else:
                        continue

                # throws ValueError if user entered a selection with no BPM attached
                # or if they entered something that can't be converted to int
                except ValueError:
                    continue
                break
            break
