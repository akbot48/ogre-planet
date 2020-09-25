#ifndef __PLANET_UTILS__
#define __PLANET_UTILS__

#include "OgrePrerequisites.h"

#include "PlanetLogger.h"


namespace OgrePlanet
{

	using namespace Ogre;

	/**Quick and dirty typdef for vector of Ogre vector3
	*/
	typedef std::vector<Vector3> VectorVector3;


	/** Basic misc utility functions
	*/
	class Utils 
	{
	public:

		/** Return vertex moved out to radius of sphere
			Does not Modify passed object
		*/
		static inline Vector3 spheriseCopy(const Vector3 &abc, Real const radius) 
		{		
			Vector3 v(abc);
			spherise(v, radius);
			return Vector3(v);
		};



		/** Move vertex out to radius of sphere
			Modifies passed object
		*/
		static inline void spherise(Vector3 &abc, Real const radius)
		{	
			// http://mathproofs.blogspot.com/2005/07/mapping-cube-to-sphere.html
			// Convert 3D point on surface of unit cube to point on surface of unit sphere
			// Normalisation (v / v.length() * radius) doesn't work well
			// Actually a 'smash -n- grab' from HexiDave Planet2 code

			Real invRadius = Real(1)/(radius);			

			// Down to unit cube
			abc *= invRadius;

			const double dX2 = abc.x * abc.x;
			const double dY2 = abc.y * abc.y;
			const double dZ2 = abc.z * abc.z;

			const double dX2Half = dX2 * 0.5;
			const double dY2Half = dY2 * 0.5;
			const double dZ2Half = dZ2 * 0.5;

			abc.x *= Math::Sqrt(1-(dY2Half)-(dZ2Half)+((dY2 * dZ2) * 0.33333333333333333333333333333333));
			abc.y *= Math::Sqrt(1-(dZ2Half)-(dX2Half)+((dZ2 * dX2) * 0.33333333333333333333333333333333));
			abc.z *= Math::Sqrt(1-(dX2Half)-(dY2Half)+((dX2 * dY2) * 0.33333333333333333333333333333333));


			// Scale back up to radius and store
			abc *= radius;
		};


		/** Get a random Real
		@param n range for return value
		@return Real in range -n -> +n
		*/
		static inline const Real randReal(Real const n = 1)
		{
			return Math::RangeRandom(-n, n);
		};

		 
		/** Get a vector contained within bounding sphere radius
		@param radius bounding radius whence returned vector must reside
		@return random vector
		*/
		static inline Vector3 randVector(Real const radius) 
		{
			Vector3 v (randReal(radius), randReal(radius), randReal(radius));
			while (v.length() > radius) 
			{
				Real x = randReal(radius);
				Real y = randReal(radius);
				Real z = randReal(radius);
				v = Vector3(x, y, z);
			}
			return Vector3(v);
		};
	};

} // namespace
#endif
