all:
	gcc -Wall -c bitmaps.c -o make_obj/bitmaps.o
	gcc -Wall -c consts.c -o make_obj/consts.o
	gcc -Wall -c helper.c -o make_obj/helper.o
	gcc -Wall -c input.c -o make_obj/input.o
	gcc -Wall -c object.c -o make_obj/object.o
	gcc -Wall -c main.c -o make_obj/main.o
	gcc -Wall -c planet.c -o make_obj/planet.o
	gcc -Wall -c value.c -o make_obj/value.o
	gcc -Wall -c vector2.c -o make_obj/vector2.o
	gcc -Wall -c map.c -o make_obj/map.o
	gcc -Wall -c wormhole.c -o make_obj/wormhole.o
	gcc -Wall -c maps.c -o make_obj/maps.o
	gcc -Wall -c animation.c -o make_obj/animation.o
	gcc -Wall -c size.c -o make_obj/size.o
	gcc -Wall -c explosion.c -o make_obj/explosion.o
	gcc -Wall -c audio.c -o make_obj/audio.o
	gcc -Wall -c entrance_animation.c -o make_obj/entrance_animation.o
	gcc -Wall -c stars.c -o make_obj/stars.o
	gcc -Wall make_obj/bitmaps.o make_obj/consts.o make_obj/helper.o make_obj/input.o make_obj/object.o make_obj/main.o make_obj/planet.o make_obj/value.o make_obj/vector2.o make_obj/map.o make_obj/wormhole.o make_obj/maps.o make_obj/animation.o make_obj/size.o make_obj/explosion.o make_obj/entrance_animation.o make_obj/audio.o make_obj/stars.o -o space -lm `pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_dialog-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_ttf-5.0 allegro_font-5.0`
