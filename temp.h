using namespace std;

mLock	.lock();
		.unlock();
		.tryLock(); // bool


class MagicObject
{
	Hash<string, MagicAttrib *> attributes;
};

class MagicAttrib
{
	virtual MagicAttrib operator+(MagicAttrib &x) = 0;
	virtual MagicAttrib operator-(MagicAttrib &x) = 0;
	virtual MagicAttrib operator*(MagicAttrib &x) = 0;
	virtual MagicAttrib operator/(MagicAttrib &x) = 0;
	virtual void clear() = 0;
}

class MagicDouble : public MagicAttrib
{
	double value;
};

class MagicString : public MagicAttrib
{
	string value;
};

class MagicDisplayObject : public MagicObject
{
public:
	virtual void display(QPaint &, QPoint &) = 0;
	
};

class MagicTom : public MagicDisplayObject
{
	
};

class MagicMapElement : public MagicDisplayObject
{
public:
	virtual bool tryMove(MagicTom &) = 0;
	virtual void move(MagicTom &) = 0;
	
	// private
	QPoint position;
	int level;
	bool enabled;
};
bool MagicMapElement::enabled = true;

class MagicWall : public MagicMapElement
{
public:
	virtual bool tryMove(MagicTom &x) {return false;}
	virtual void move(MagicTom &x) {}
}

class MagicFloor : public MagicMapElement
{
public:
	virtual bool moveTo(MagicTom &x) {return true;}
	virtual void move(MagicTom &x) {}
}

class MagicThing : public MagicMapElement
{
	
};

class MagicEnemy : public MagicMapElement
{
	
};

