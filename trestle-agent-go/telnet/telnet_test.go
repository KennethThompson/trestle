package telnet_test

import (
	"testing"

	"github.com/reiver/go-telnet"
)

func TestTelnet(t *testing.T) {

	var handler telnet.Handler = telnet.EchoHandler

	err := telnet.ListenAndServe(":5555", handler)
	if nil != err {
		//@TODO: Handle this error better.
		panic(err)
	}
}
