#include "SolidNoise.h"
#include "RNG.h"
SolidNoise::SolidNoise()
{
	RNG random;
	int i;

	grad[0] = Vector3D( 1, 1, 0);
	grad[1] = Vector3D(-1, 1, 0);
	grad[2] = Vector3D( 1,-1, 0);
	grad[3] = Vector3D(-1,-1, 0);

	grad[4] = Vector3D( 1, 0, 1);
	grad[5] = Vector3D(-1, 0, 1);
	grad[6] = Vector3D( 1, 0,-1);
	grad[7] = Vector3D(-1, 0,-1);

	grad[8] =  Vector3D( 0, 1, 1);
	grad[9] =  Vector3D( 0,-1, 1);
	grad[10] = Vector3D( 0, 1,-1);
	grad[11] = Vector3D( 0,-1,-1);

	grad[12] = Vector3D( 1, 1, 0);
	grad[13] = Vector3D(-1, 1, 0);
	grad[14] = Vector3D( 0,-1, 1);
	grad[15] = Vector3D( 0,-1,-1);

	for (i=0; i< 16; i++) 
		phi[i] = i;

	//shuffle phi
	for (i = 14; i >= 0; i--) {
		int target = int(random()*i);
		int temp = phi[i+1];
		phi[i+1] = phi[target];
		phi[target] = temp;
	}
}

float SolidNoise::turbulence(const Vector3D& p, int depth) const
{
	float sum = 0.0f;
	float weight = 1.0f;
	Vector3D ptemp(p);

	sum = fabs(noise(ptemp));

	for(int i = 1; i <depth; i++)
	{
		weight = weight * 2.0;
		ptemp.setX(p.getX() * weight);
		ptemp.setY(p.getY() * weight);
		ptemp.setZ(p.getZ() * weight);

		sum += fabs(noise(ptemp)) / weight;
	}
	return sum;
}

float SolidNoise::dturbulence(const Vector3D& p, int depth, float d)
	const {
		float sum = 0.0f;
		float weight = 1.0f;
		Vector3D ptemp(p);
		sum += fabs(noise(ptemp))/d;
		for (int i =1; i < depth; i++)
		{
			weight = weight * d;
			ptemp.setX(p.getX()*weight);
			ptemp.setY(p.getY()*weight);
			ptemp.setZ(p.getZ()*weight);
			sum += fabs(noise(ptemp)) /d;
		}
		return sum;
}

float SolidNoise::noise(const Vector3D& p) const {
	int fi, fj, fk;
	float fu, fv, fw, sum;
	Vector3D v;
	fi = int(floor(p.getX()));
	fj = int(floor(p.getY()));
	fk = int(floor(p.getZ()));
	fu = p.getX() - float(fi);
	fv = p.getY() - float(fj);
	fw = p.getZ() - float(fk);
	sum = 0.0;

	v = Vector3D(fu, fv, fw);
	sum += knot(fi, fj, fk, v);

	v = Vector3D(fu - 1, fv, fw);
	sum += knot(fi+1, fj, fk, v);

	v = Vector3D(fu, fv -1, fw);
	sum += knot(fi, fj + 1, fk, v);

	v = Vector3D(fu, fv, fw - 1);
	sum += knot(fi, fj, fk+1, v);

	v = Vector3D(fu - 1, fv - 1, fw);
	sum += knot(fi+1, fj + 1, fk, v);

	v = Vector3D(fu - 1, fv, fw-1);
	sum += knot(fi+1, fj, fk+1, v);

	v = Vector3D(fu, fv-1, fw-1);
	sum += knot(fi, fj+1, fk+1, v);

	v = Vector3D(fu - 1, fv -1, fw-1);
	sum += knot(fi+1, fj + 1, fk+1, v);

	return sum;
}
	