#include"libOne.h"
#include"VEC.h"

struct BEETLE {
	struct VEC pos;
	float advSpeed = 0;
	float angle = 0;
	float angSpeed = 0;
};


void gmain() {
	window(1920, 1080, 1);

	angleMode(DEGREES);



	int osuImg = loadImage("assets\\osu.png");
	int mesuImg = loadImage("assets\\mesu.png");
	int backImg = loadImage("assets\\green.png");

	struct BEETLE osu;
	osu.pos.x = width / 2 + 500;
	osu.pos.y = height / 2;
	osu.advSpeed = 5;

	struct BEETLE mesu;
	mesu.pos.x = 200;
	mesu.pos.y = height / 2;
	mesu.advSpeed = 5;
	float advAngle = 0;

	const int WALK = 0;
	const int ROTATE = 1;
	int state = WALK;
	int rotateCount = 0;

	while (notQuit) {
		clear();
		if (isTrigger(KEY_ENTER)) {
			osu.pos.x = width / 2 + 500;
			osu.pos.y = height / 2;
		}
		if (state == WALK) {
			struct VEC a, b;
			if (isPress(KEY_D) || isPress(KEY_RIGHT))b.x = 1;
			if (isPress(KEY_A) || isPress(KEY_LEFT))b.x = -1;
			if (isPress(KEY_W) || isPress(KEY_UP))b.y = -1;
			if (isPress(KEY_S) || isPress(KEY_DOWN))b.y = 1;

			if (b.x != 0 || b.y != 0) {
				b = normalize(&b);
				osu.pos.x += b.x * osu.advSpeed;
				osu.pos.y += b.y * osu.advSpeed;

				a = vecFromAngle(osu.angle);
				osu.angSpeed = angleBetweenTwoVecs(&a, &b) / 8;
				osu.angle += osu.angSpeed;
			}

			b.x = sin(advAngle);
			b.y = -cos(advAngle) * 0.4f;

			b = normalize(&b);
			mesu.pos.x += b.x * mesu.advSpeed;
			mesu.pos.y += b.y * mesu.advSpeed;
			advAngle += 0.48f;

			a = vecFromAngle(mesu.angle);
			mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / 8;
			mesu.angle += mesu.angSpeed;

			if (isTrigger(KEY_SPACE)) {
				b.x = mesu.pos.x - osu.pos.x;
				b.y = mesu.pos.y - osu.pos.y;
				if (magnitude(&b) < 300) {
					a = vecFromAngle(osu.angle);
					osu.angSpeed = angleBetweenTwoVecs(&a, &b) / 60;

					b.x = -b.x;
					b.y = -b.y;
					a = vecFromAngle(mesu.angle);
					mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / 60;

					rotateCount = 0;


					state = ROTATE;
				}
			}
		}
		else if (state == ROTATE) {
			if (rotateCount < 60) {
				osu.angle += osu.angSpeed;
				mesu.angle += mesu.angSpeed;
				rotateCount++;
			}
			else {
				if (isTrigger(KEY_W) || isTrigger(KEY_UP) ||
					isTrigger(KEY_A) || isTrigger(KEY_LEFT) ||
					isTrigger(KEY_S) || isTrigger(KEY_DOWN) ||
					isTrigger(KEY_D) || isTrigger(KEY_RIGHT)){
					state = WALK;
				}
			}
		}


		rectMode(CORNER);
		image(backImg, 0, 0);

		noStroke();
		fill(224, 225, 204, 60);
		circle(mesu.pos.x, mesu.pos.y, 600);

		rectMode(CENTER);
		image(mesuImg, mesu.pos.x, mesu.pos.y, mesu.angle);
		image(osuImg, osu.pos.x, osu.pos.y, osu.angle);


	}

}