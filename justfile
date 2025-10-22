set shell := ["bash", "-cu"]

start:
    podman-compose -f mqtt_broker/broker.yml up -d 

stop:
    podman-compose -f mqtt_broker/broker.yml down 

status:
    podman-compose -f mqtt_broker/broker.yml ps 

logs:
    podman-compose -f mqtt_broker/broker.yml logs 

restart: stop start

shell:
    podman exec -it mosquitto /bin/sh

publish topic message:
    podman exec mosquitto mosquitto_pub -h localhost -t {{topic}} -m "{{message}}"

subscribe topic:
    podman exec -it mosquitto mosquitto_sub -h localhost -t {{topic}}
