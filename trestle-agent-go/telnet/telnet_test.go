package telnet_test

import (
	"log"
	"testing"

	"github.com/reiver/go-telnet"
)

func TestTelnet(t *testing.T) {
	tel.launch_telnet()
	log.Printf(" [*] Waiting for messages. To exit press CTRL+C")
	var handler telnet.Handler = telnet.EchoHandler

	err := telnet.ListenAndServe(":5555", handler)
	if nil != err {
		//@TODO: Handle this error better.
		panic(err)
	}
}
