FROM php:8.2.6-fpm-alpine

# Install packages
RUN apk add --no-cache bash

# Xdebug
# ARG INSTALL_XDEBUG=false
# RUN if [ ${INSTALL_XDEBUG} = true ]; \
#     then \
#       pecl install xdebug && docker-php-ext-enable xdebug; \
#     fi;

# COPY ./docker/php-fpm/xdebug.ini /usr/local/etc/php/conf.d/xdebug.ini

# Postgres
RUN apk add --no-cache libpq-dev && docker-php-ext-install pdo_pgsql

# Memory limit
RUN cd /usr/local/etc/php/conf.d/ && \
  echo 'memory_limit = -1' >> /usr/local/etc/php/conf.d/docker-php-memlimit.ini

# Configure non-root user.
ARG PUID=1000
ARG PGID=1000
RUN apk --no-cache add shadow && \
    groupmod -o -g ${PGID} www-data && \
    usermod -o -u ${PUID} -g www-data www-data

# Source code
RUN chown www-data:www-data /var/www
COPY --chown=www-data:www-data ./ /var/www
WORKDIR /var/www

USER www-data

# Composer
COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

CMD composer install && \ 
  php-fpm

EXPOSE 9000