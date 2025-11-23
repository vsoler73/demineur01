#include <QObject>
#include <QMutex>

#include "Level.h"

class QTimer ;

class DemineurGame: public QObject
{
    Q_OBJECT
    
	public:
        DemineurGame() ;

		void init(const Level& level) ;

		const Level& currentState() const { return mLevelState ;}
		Level& currentState() { return mLevelState ;}

		void stop();
		void start();
        
signals:
        	void changed() ;
            
	private:
			void explode(Level &level, int i, int j);
            //bool test_bestiole(const Level& L,int x,int y) const;

		Level mLevelState ;
        
        	QTimer *mTimer ;
            	QMutex mtx ;
};
