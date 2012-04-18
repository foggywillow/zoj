#include <stdio.h>
#include <math.h>

typedef struct vector
{
	int x;
	int y;
	int z;
}point, vector;

typedef struct vectorF
{
	double x;
	double y;
	double z;
}pointF, vectorF;


pointF toPointF(point p)
{
	pointF pf;
	pf.x = (double)(p.x);
	pf.y = (double)(p.y);
	pf.z = (double)(p.z);

	return pf;
}

vectorF toVectorF(vector v)
{
	vectorF vf;
	vf.x = (double)(v.x);
	vf.y = (double)(v.y);
	vf.z = (double)(v.z);

	return vf;
}

/* Get Vector From two Point */
vector getVector(point start, point end)
{
	vector v;
	v.x = end.x - start.x;
	v.y = end.y - start.y;
	v.z = end.z - start.z;

	return v;
}

vectorF getVectorF(pointF start, pointF end)
{
	vectorF v;
	v.x = end.x - start.x;
	v.y = end.y - start.y;
	v.z = end.z - start.z;

	return v;
}

point getPoint(point start, vector d)
{
	point p;
	p.x = start.x + d.x;
	p.y = start.y + d.y;
	p.z = start.z + d.z;

	return p;
}

pointF getPointF(pointF start, vectorF d)
{
	pointF p;
	p.x = start.x + d.x;
	p.y = start.y + d.y;
	p.z = start.z + d.z;

	return p;
}

double vectorMultiply(vectorF va, vectorF vb)
{
	return (va.x*vb.x + va.y*vb.y + va.z*vb.z);
}

double getLength(vectorF v)
{
	return sqrt(vectorMultiply(v, v));
}

double getDistance(pointF pa, pointF pb)
{
	vectorF v = getVectorF(pa, pb);
	double d = vectorMultiply(v, v);
	return sqrt(d);
}

/* get Normal Vector of a plane defined by sa and sb */
vectorF getPlaneNormalVector(vectorF sa, vectorF sb)
{
	vectorF vn;
	double l;

	vn.x = sa.y*sb.z - sa.z*sb.y;
	vn.y = sa.z*sb.x - sa.x*sb.z;
	vn.z = sa.x*sb.y - sa.y*sb.x;

	l = getLength(vn);
	vn.x /= l;
	vn.y /= l;
	vn.z /= l;

	return vn;
}

/* calculate the coordinate of the intersection of a line and a plane */
pointF getIntersection(pointF p, vectorF v, pointF sp, vectorF vn)
{
	pointF pi;
	double vpt, t;

	vpt = vectorMultiply(v,vn);
	if (vpt == 0)
		pi.x = pi.y = pi.z = -1;
	else
	{
		t = vectorMultiply(getVectorF(p,sp), vn) / vpt;
		if (t < 0)
			pi.x = pi.y = pi.z = -1;
		else
		{
			pi.x = p.x + t * v.x;
			pi.y = p.y + t * v.y;
			pi.z = p.z + t * v.z;
		}
	}

	return pi;
}

double getDistanceOfPointToLine(pointF p, pointF lp, vectorF lv)
{
	double d, t1, t2;
	vectorF t, v;

	t2 = getLength(lv);
	t = getVectorF(p, lp);
	v.x = lv.y*t.z - lv.z*t.y;
	v.y = lv.z*t.x - lv.x*t.z;
	v.z = lv.x*t.y - lv.y*t.x;  /* v = lv x t */
	t1 = getLength(v);
	d = t1 / t2;

	return d;
}

int isPointInRegion(pointF p, point pa, point pb, point pc, point pd)
{
	double d1, d2;
	double d;
	d1 = getDistanceOfPointToLine(toPointF(pd), toPointF(pa), toVectorF(getVector(pa, pb)));
	d2 = getDistanceOfPointToLine(toPointF(pd), toPointF(pb), toVectorF(getVector(pb, pc)));

	d = getDistanceOfPointToLine(p, toPointF(pa), toVectorF(getVector(pa, pb)));
	if (d >= d1)
		return 0;
	d = getDistanceOfPointToLine(p, toPointF(pd), toVectorF(getVector(pd, pc)));
	if (d >= d1)
		return 0;
	d = getDistanceOfPointToLine(p, toPointF(pb), toVectorF(getVector(pb, pc)));
	if (d >= d2)
		return 0;
	d = getDistanceOfPointToLine(p, toPointF(pa), toVectorF(getVector(pa, pd)));
	if (d >= d2)
		return 0;
	
	return 1;
}

void NormalVector(vectorF *v)
{
	double l = getLength(*v);
	v->x /= l;
	v->y /= l;
	v->z /= l;
}

int main()
{
	int T;
	point lstart, lend;
	point pv;  /* vertex A of the prism */
	point pa, pb, pc;  /* three adjacent vertex of A */
	point pd, pe, pf, pg;  /* other point */
	/* Parallelepiped: Vadb-cegf */
	double r;  /* refractive index */

	pointF plaser;  /* point of laser "start" */
	vectorF dlaser;  /* laser direction */

	vector px, py, pz;  /* vectors of Parallelepiped */
	vectorF pnx, pny, pnz;  /* normal vectors of each surfaces of Parallelepiped */
	vectorF pn;  /* normal vectors of one surface */

	vectorF vBase;  /* ground (0,0,1) */
	pointF pBase;  /* ground (0,0,0) */

	double distance, dt;
	pointF t, pi;

	double cos1, cos2, P;
	double n1, n2;

	int planeindex, lastplaneindex;
	int i;
	int flag;

	vBase.x = vBase.y = 0;
	vBase.z = 1;
	pBase.x = pBase.y = pBase.z = 0;

	scanf("%d",&T);

	while (T--)
	{
		scanf("%d%d%d", &lstart.x, &lstart.y, &lstart.z);
		scanf("%d%d%d", &lend.x, &lend.y, &lend.z);
		scanf("%d%d%d", &pv.x, &pv.y, &pv.z);
		scanf("%d%d%d", &pa.x, &pa.y, &pa.z);
		scanf("%d%d%d", &pb.x, &pb.y, &pb.z);
		scanf("%d%d%d", &pc.x, &pc.y, &pc.z);
		scanf("%lf", &r);

		px = getVector(pv, pa);
		py = getVector(pv, pb);
		pz = getVector(pv, pc);

		pd = getPoint(pa, py);
		pe = getPoint(pa, pz);
		pf = getPoint(pb, pz);
		pg = getPoint(pd, pz);
		
		pnx = getPlaneNormalVector(toVectorF(py), toVectorF(pz));
		pny = getPlaneNormalVector(toVectorF(px), toVectorF(pz));
		pnz = getPlaneNormalVector(toVectorF(px), toVectorF(py));

		plaser = toVectorF(lstart);
		dlaser = toVectorF(getVector(lstart, lend));
		NormalVector(&dlaser);

		lastplaneindex = planeindex = 0;
		for (i = 1; ; i++)
		{
			distance = 0;
			/* surf vadb, index 1 */
			t = getIntersection(plaser, dlaser, toPointF(pv), pnz);
			if (t.z > 0 && lastplaneindex != 1 && isPointInRegion(t, pv, pa, pd, pb))
			{
				dt = getDistance(plaser, t);
				if (dt == 0)
					break;

				if (dt < distance || distance == 0)
				{
					pi = t;
					distance = dt;
					planeindex = 1;
				}
			}
			/* surf vcfb, index 2 */
			t = getIntersection(plaser, dlaser, toPointF(pv), pnx);
			if (t.z > 0 && lastplaneindex != 2 && isPointInRegion(t, pv, pc, pf, pb))
			{
				dt = getDistance(plaser, t);
				if (dt == 0)
					break;
				if (dt < distance || distance == 0)
				{
					pi = t;
					distance = dt;
					planeindex = 2;
				}
			}
			/* surf aecv, index 3 */
			t = getIntersection(plaser, dlaser, toPointF(pa), pny);
			if (t.z > 0 && lastplaneindex != 3 && isPointInRegion(t, pa, pe, pc, pv))
			{
				dt = getDistance(plaser, t);
				if (dt == 0)
					break;
				if (dt < distance || distance == 0)
				{
					pi = t;
					distance = dt;
					planeindex = 3;
				}
			}
			/*surf cegf, index 4 */
			t = getIntersection(plaser, dlaser, toPointF(pc), pnz);
			if (t.z > 0 && lastplaneindex != 4 && isPointInRegion(t, pc, pe, pg, pf))
			{
				dt = getDistance(plaser, t);
				if (dt == 0)
					break;
				if (dt < distance || distance == 0)
				{
					pi = t;
					distance = dt;
					planeindex = 4;
				}
			}
			/*surf aegd, index 5 */
			t = getIntersection(plaser, dlaser, toPointF(pa), pnx);
			if (t.z > 0 && lastplaneindex != 5 && isPointInRegion(t, pa, pe, pg, pd))
			{
				dt = getDistance(plaser, t);
				if (dt == 0)
					break;
				if (dt < distance || distance == 0)
				{
					pi = t;
					distance = dt;
					planeindex = 5;
				}
			}
			/*surf dgfb, index 6 */
			t = getIntersection(plaser, dlaser, toPointF(pd), pny);
			if (t.z > 0 && lastplaneindex != 6 && isPointInRegion(t, pd, pg, pf, pb))
			{
				dt = getDistance(plaser, t);
				if (dt == 0)
					break;
				if (dt < distance || distance == 0)
				{
					pi = t;
					distance = dt;
					planeindex = 6;
				}
			}

			if (planeindex == lastplaneindex)
				break;

			if (planeindex == 1 || planeindex == 4)
				pn = pnz;
			else if (planeindex == 2 || planeindex == 5)
				pn = pnx;
			else if (planeindex == 3 || planeindex == 6)
				pn = pny;
			else
				break;

			lastplaneindex = planeindex;
			plaser = pi;

			/* 
			 * Vector form of Snell's Law 
			 * Reference: http://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
			 */
			if (i % 2)
			{
				n1 = 1;
				n2 = r;
			}
			else
			{
				n1 = r;
				n2 = 1;
			}
			
			dlaser.x = -dlaser.x;
			dlaser.y = -dlaser.y;
			dlaser.z = -dlaser.z;

			cos1 = vectorMultiply(dlaser, pn) / (getLength(dlaser) * getLength(pn));

			dlaser.x = -dlaser.x;
			dlaser.y = -dlaser.y;
			dlaser.z = -dlaser.z;

			cos2 = sqrt(1-(n1/n2)*(n1/n2)*(1-cos1*cos1));

			if (cos1 <= 0)
				flag = -1;
			else
				flag = 1;

			dlaser.x = (n1/n2)*dlaser.x + flag*(n1/n2*cos1-cos2)*pn.x;
			dlaser.y = (n1/n2)*dlaser.y + flag*(n1/n2*cos1-cos2)*pn.y;
			dlaser.z = (n1/n2)*dlaser.z + flag*(n1/n2*cos1-cos2)*pn.z;
			
		}

		if (dlaser.z >= 0)
			printf("Error\n");
		else
		{
			t = getIntersection(plaser, dlaser, pBase, vBase);
			printf("%.3lf %.3lf\n", t.x, t.y);
		}
	}

	return 0;
}
