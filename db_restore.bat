docker volume rm zlp-library_postgres zlp-library_pgadmin
@REM docker volume create zlp-library_postgres zlp-library_pgadmin
docker run --rm -v zlp-library_postgres:/dbdata-volume -v zlp-library_pgadmin:/pgadata-volume -v %cd%/dbdata:/dbdata busybox sh -c "tar -xvzf /dbdata/zlp-library_postgres.tar.gz -C / && tar -xvzf /dbdata/zlp-library_pgadmin.tar.gz -C /"