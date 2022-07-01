FROM debian:latest

RUN apt-get update && apt-get install curl git ca-certificates -qy --no-install-recommends
RUN adduser --uid 6789 --disabled-password --home /home/app -c "app runner user" --shell /bin/bash app

RUN mkdir -p /home/linuxbrew/.linuxbrew/Homebrew
RUN chown -R app:app /home

USER app
RUN /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

ENV PATH=${PATH}:/home/linuxbrew/.linuxbrew/bin

RUN brew install gcc && \
    brew install opencv && \
    brew install dlib && \
    brew install pkg-config && \
    brew link opencv && \
    brew link dlib
RUN pkg-config --modversion opencv4 && \
    pkg-config --modversion dlib-1
