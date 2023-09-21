SRCS	=	./docker-compose.yml

all:
	docker-compose -f $(SRCS) up --build -d
	docker container exec -it nm fish

start:
	docker-compose -f $(SRCS) start

stop:
	docker-compose -f $(SRCS) stop

down:
	docker-compose -f $(SRCS) down

ps:
	docker-compose -f $(SRCS) ps

fclean:
	docker stop $$(docker ps -qa);\
    docker rm $$(docker ps -qa);\
    docker rmi -f $$(docker images -qa);\
	docker system prune -af
	docker volume prune -af

re: fclean
	@$(MAKE) all

prune:
	docker system prune -f
	docker volume prune -f

.PHONY:	all up down ps top clean fclean prune
