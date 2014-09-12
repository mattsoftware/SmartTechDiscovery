#!/usr/bin/python
#	From http://www.instructables.com/id/Getting-Stock-Prices-on-Raspberry-Pi-Python
#	sudo pip install ystockquote
#	Get the price for just 1 ticker if supplied, excess parameters ignored
#	David Tangye <DavidTangye@gmail.com> - 01/09/2014 15:25:08
import sys
import ystockquote

def main(ticker):
	if ( ticker != "" ) :
		allInfo = ystockquote.get_all(ticker)
		if ( allInfo["price"] != "0.00" ) :
			print allInfo["price"]

if __name__ == "__main__":
    main(sys.argv[1])
