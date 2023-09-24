package telnet_srv_test

import (
	"log"
	"testing"

	"github.com/reiver/go-telnet"
	//tel "github.com/kenneththompson/trestle/trestle-agent-go"
)

func TestTelnet(t *testing.T) {

	log.Printf(" [*] Waiting for messages. To exit press CTRL+C")
	var handler telnet.Handler = telnet.EchoHandler

	err := telnet.ListenAndServe(":5555", handler)
	if nil != err {
		//@TODO: Handle this error better.
		panic(err)
	}
}
