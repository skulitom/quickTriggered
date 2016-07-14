#ifndef FigureType_H
#define FigureType_H

#define MAX_PROB 600
#define MIN_PROB 0

#define MEXICANS 0
#define JEWS 1
#define WOMEN 2
#define BLACK 3
#define ASIAN 4
#define WHITE_SUPREME 5


class FigureType {
public:
	FigureType(int type, int prob, int morale);
	~FigureType();
protected:
private:
	int numberOfTurns;
	int maxTurns;
};

#endif

