FROM        debian:buster
LABEL       authors="tnoulens"
RUN	        apt update && \
            apt upgrade -y && \
            apt install -y curl \
            vim \
            fish \
            make \
            usermode \
            git \
            gcc \
            gcc-multilib \
            gdb \
            valgrind
COPY        ./run.sh .
RUN	        chmod +x ./run.sh && mkdir ft_nm
WORKDIR     ./ft_nm
COPY        ./code .
RUN	        make
ENTRYPOINT  ["/run.sh"]
