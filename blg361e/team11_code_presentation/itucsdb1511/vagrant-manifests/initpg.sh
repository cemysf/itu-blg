#!/bin/sh

sudo perl -pi -e "s/#listen_addresses = 'localhost'/listen_addresses = '*'/" /etc/postgresql/9.3/main/postgresql.conf
sudo perl -pi -e "s/127.0.0.1\/32/all/" /etc/postgresql/9.3/main/pg_hba.conf
sudo service postgresql restart

AS_POSTGRES="sudo -u postgres -H"
AS_VAGRANT="sudo -u vagrant -H"

$AS_POSTGRES bash -c "psql -c \"CREATE USER vagrant WITH PASSWORD 'vagrant' CREATEDB;\""
$AS_VAGRANT createdb itucsdb
