#include <QObject>
#include <QMutex>

#include "Level.h"


class DemineurGame: public QObject
{   
	public:
    DemineurGame() {}

		void init(const Level& level) ;

		const Level& currentState() const { return mLevelState ;}
		Level& currentState() { return mLevelState ;}

	private:
		Level mLevelState ;
};
