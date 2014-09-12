#!/usr/bin/python
#	From http://www.instructables.com/id/Getting-Stock-Prices-on-Raspberry-Pi-Python
#	sudo pip install ystockquote
#	David Tangye <DavidTangye@gmail.com> - 01/09/2014 15:25:08
import sys
import ystockquote

def main(tickers):
	for ticker in tickers:
		allInfo = ystockquote.get_all(ticker)
		print ticker + ":Exchange=" + allInfo["stock_exchange"] \
		+ ":Cap=" + allInfo["market_cap"] \
		+ ":P-Earn=" + allInfo["price_earnings_ratio"] \
		+ ":P-Sales=" + allInfo["price_sales_ratio"] \
		+ ":Range52=" + allInfo["fifty_two_week_low"] \
		+ "-" + allInfo["fifty_two_week_high"] \
		+ ":Price=" + allInfo["price"]

if __name__ == "__main__":
    main(sys.argv[1:])
