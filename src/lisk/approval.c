//
// Created by andrea on 09/12/18.
//

#include "approval.h"
#include "../ui_utils.h"
#include "../io.h"
#include "./liskutils.h"
#include "./ui_elements_s.h"
#include "os_io_seproxyhal.h"
#include "ed25519.h"


/**
 * Sign with address
 */
void touch_deny() {
  G_io_apdu_buffer[0] = 0x69;
  G_io_apdu_buffer[1] = 0x85;

  // Allow restart of operation
  commContext.started = false;
  commContext.read = 0;

  // Kill private key - shouldn't be necessary but just in case.
  os_memset(&signContext.privateKey, 0, sizeof(signContext.privateKey));

  // Send back the response, do not restart the event loop
  io_exchange(CHANNEL_APDU | IO_RETURN_AFTER_TX, 2);

  // Display back the original UX
  ui_idle();
}

void touch_approve() {
  uint8_t signature[64];
  sign(&signContext.privateKey, signContext.digest, 32, signature);
  initResponse();
  addToResponse(signature, 64);

  // Allow restart of operation
  commContext.started = false;
  commContext.read = 0;

  unsigned int tx = flushResponseToIO(G_io_apdu_buffer);
  G_io_apdu_buffer[tx]   = 0x90;
  G_io_apdu_buffer[tx+1] = 0x00;

  io_exchange(CHANNEL_APDU | IO_RETURN_AFTER_TX, tx+2);

  // Display back the original UX
  ui_idle();
}
