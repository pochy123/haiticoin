To run

#Make sure tor is started
sudo systemctl start tor.service

#start trigger daemon with tor as proxy
ONIONHOSTNAME=$(sudo cat /var/lib/tor/ppcoin-service/hostname)
./triggerd -daemon -proxy=127.0.0.1:9050 -bind=127.0.0.1 -externalip=${ONIONHOSTNAME}
