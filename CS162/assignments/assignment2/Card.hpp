#pragma once

class Card {

	private:
		int rank; // range from 0 - 12
		int suit; // range from 0 - 3

	public:
		Card();

		int GetRank() const;
		int GetSuit() const;
		void SetRank(int);
		void SetSuit(int);
		void SetSuit(std::string);
		std::string GetSuitString() const;
		std::string GetRankString() const;
};