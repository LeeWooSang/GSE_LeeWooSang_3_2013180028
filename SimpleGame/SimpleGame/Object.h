#pragma once
class Object
{
public:
	Object(float x, float y, int type, int teamType);
	~Object();

public:
	float Get_X()																		{ return m_fx; }
	void Set_X(float val)																{ m_fx = val; }

	float Get_Y()																		{ return m_fy; }
	void Set_Y(float val)																{ m_fy = val; }

	float Get_Z()																		{ return m_fz; }
	void Set_Z(float val)																{ m_fz = val; }

	float Get_Size()																	{ return m_fsize; }
	void Set_Size(float val)															{ m_fsize = val; }

	float Get_Color_R()																{ return m_color[0]; }
	float Get_Color_G()																{ return m_color[1]; }
	float Get_Color_B()																{ return m_color[2]; }
	float Get_Color_A()																{ return m_color[3]; }

	void Set_Color(float red, float green, float blue, float alpha)		{ m_color[0] = red, m_color[1] = green, m_color[2] = blue, m_color[3] = alpha; }

	bool Get_IsColision()															{ return m_isColision; }
	void Set_IsColision(bool a)													{ m_isColision = a; }

	float Get_HalfSize()																{ return m_fsize *0.5f; }

	float Get_Life()																	{ return m_life; }
	void Set_Life(float val)															{ m_life = val; }

	float Get_LifeTime()																{ return m_lifeTime; }

	float Get_Speed()																	{ return m_fspeed; }
	void Set_Speed(float val)														{ m_fspeed = val; }

	int Get_Type()																		{ return m_type; }
	void Set_Type(int type)															{ m_type = type; }

	float Get_LastBullet()															{ return m_lastBullet; }
	void Set_LastBullet(float val)													{ m_lastBullet = val; }

	float Get_LastArrow()															{ return m_lastArrow; }
	void Set_LastArrow(float val)													{ m_lastArrow = val; }

	int Get_ParentID()																{ return m_parentID;  }
	void Set_ParentID(int val)														{ m_parentID = val; }

	int Get_TeamType()																{ return m_teamType;  }
	void Set_TeamType(int val)													{ m_teamType = val; }

	void Set_Damage(float amount)											{ m_life -= amount; }

public:
	void Update(float elapsedTime );

private:
	float m_fx;
	float m_fy;
	float m_fz;
	float m_fsize;
	float m_color[4];		// R G B A


	float m_vector[2];	// vectorX, vectorY
	float m_fspeed;

	// is colision ?
	bool m_isColision;

	// Life
	float m_life;
	float m_lifeTime;
	int m_type;

	float m_lastBullet;
	float m_lastArrow;

	int m_parentID;
	int m_teamType;
};

