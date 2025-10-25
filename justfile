set shell := ["bash", "-cu"]

[no-cd]
start:
    cd mqtt_broker && podman-compose -f broker.yml up -d 

[no-cd]
stop:
    cd mqtt_broker && podman-compose -f broker.yml down 

[no-cd]
status:
    cd mqtt_broker && podman-compose -f broker.yml ps 

[no-cd]
logs:
    cd mqtt_broker && podman-compose -f broker.yml logs 

restart: stop start

shell:
    podman exec -it mosquitto /bin/sh

publish topic message:
    podman exec mosquitto mosquitto_pub -h localhost -t {{topic}} -m "{{message}}"

subscribe topic:
    podman exec -it mosquitto mosquitto_sub -h localhost -t {{topic}}
