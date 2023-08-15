#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void saveScore(int savedScore){
    	score = savedScore;
    }

    int getScore(){
    	return score;
    }
    void saveHighestScore(int savedHighestScore){
    	highestScore = savedHighestScore;
    }

	int getHighestScore(){
		return highestScore;
	}
protected:
    ModelListener* modelListener;
    int score;
    int highestScore;
};

#endif // MODEL_HPP
