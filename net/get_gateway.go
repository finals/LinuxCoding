package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"strings"
        "bytes"
)

func main() {
	netConfig, err := ioutil.ReadFile("interfaces")
	if err != nil {
	//	log.Errorf("Read network config: /etc/network/interfaces error: %s", err.Error())
		return
	}

	scanner := bufio.NewScanner(bytes.NewReader(netConfig))
	gateways := []string{}
	for scanner.Scan() {
		line := scanner.Text()
		if strings.HasPrefix(line, "gateway") {
			data := strings.Split(line, " ")
			if len(data) == 2 /*&& ip.IsValidIPv4(data[1])*/ {
				gateways = append(gateways, data[1])
			}
		}
	}

	for _, gw := range gateways {
		fmt.Println(gw)
	}
}
