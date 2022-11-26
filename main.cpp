#include <SFML/Graphics.hpp>
using namespace sf;

float offsetX = 0, offsetY = 0;

const int H = 13;
const int W = 40;

String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                    B",
"B     BB                             B",
"BBB          BBB     BBB             B",
"B            BBB     BBB             B",
"B            BBB     BBB             B",
"BBBBBB     BBBBBBBBBBBBBBBBB     BBBBB",
"B           BBBBBBBBBBBBBB           B",
"B        BBBBBBBBBBBBBBBBB       BBBBB",
"B           BBBBBBBBBBBBBB           B",
"BBBB        BBBBBBBBBBBBBBBBBB       B",
"            BBBBBBBBBBBBBB            ",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture& image) {
		sprite.setTexture(image);
		rect = FloatRect(40 * 10, 39 * 10, 33, 40);

		dx = dy = 0.1;
		currentFrame = 0;
	}

	void update(float time) {

		rect.left += dx * time;
		Collision(0);

		if (!onGround) dy = dy + 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(1);

		currentFrame += 0.005 * time;
		if (currentFrame > 6) currentFrame -= 6;

		if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
		if (dx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}


};

int main() {
	RenderWindow window(VideoMode(600, 400), "platformer");

	Texture t;
	t.loadFromFile("_Run.png");

	float currentFrame = 0;

	PLAYER p(t);

	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;
		
		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dx = -0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (p.onGround) {
				p.dy = 0.25; p.onGround = false;
			}
		}

		p.update(time);

		if (p.rect.left > 300) offsetX = p.rect.left - 300;
		offsetY = p.rect.top - 200;

		window.clear(Color::White);

		for (int i = 0; i < W; i++) {
			if (TileMap[i][i] == '0')rectangle.setFillColor(Color::Black);

			if (TileMap[i][i] == '0')rectangle.setFillColor(Color::Green);

			if (TileMap[i][i] == ' ') continue;

			rectangle.setPosition(i * 32 - offsetX, offsetY, i * 32 - offsetY);
			window.draw(rectangle);
		}

		window.draw(p.sprite);
		window.display();
	}

	return 0;
}