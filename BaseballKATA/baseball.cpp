#include <stdexcept>

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

using namespace std;
class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question) {
	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		if (guessNumber == question) {
			return { true, 3, 0 };
		}
		pair<int, int> strikesBalls = getStrikesBalls(guessNumber);
		return { false, strikesBalls.first, strikesBalls.second};
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicateNumber(guessNumber)) {
			throw invalid_argument("Must not have same number");
		}
	}

	bool isDuplicateNumber(const std::string& guessNumber)
	{
		return (guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2]);
	}

	pair<int, int> getStrikesBalls(const string& guessNumber) {
		int strikesCnt = 0;
		int ballCnts = 0;
		for (int num = 0; num < guessNumber.size(); num++) {
			if (guessNumber[num] == question[num]) {
				strikesCnt++;
				continue;
			}
			for (int otherNum = 0; otherNum < guessNumber.size(); otherNum++) {
				if (guessNumber[num] == question[otherNum]) {
					ballCnts++;
				}
			}
		}
		return { strikesCnt, ballCnts };
	}

private:
	string question;
};