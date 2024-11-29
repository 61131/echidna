#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <cast.h>
#include <echidna.h>
#include <ll.h>
#include <log.h>
#include <runtime.h>
#include <runtime/error.h>
#include <value.h>

#include <hardware/piface.h>

#ifndef _MSC_VER
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


/*
    This source file implements support for the PiFace Digital I/O board for the 
    Raspberry Pi. This interface board incorporates MCP23S17 16-bit I/O expander 
    with serial interface to provide eight digital inputs and eight digital outputs.
    Support is implemented through the addition of two new functions, piface_read
    and piface_write, which perform read and write operations respectively for 
    these I/O lines.
*/

static int _piface_read(PIFACE *Context, uint8_t Reg, uint8_t *Val);

static int _piface_write(PIFACE *Context, uint8_t Reg, uint8_t Val);


static int
_piface_read(PIFACE *Context, uint8_t Reg, uint8_t *Val) {
    struct spi_ioc_transfer sMsg;
    uint8_t uBuffer[3];

    //  Control Byte: 0 1 0 0 A2 A1 A0 1

    uBuffer[0] = 0x41 | ((Context->Address << 1) & 0xe);
    uBuffer[1] = Reg;
    uBuffer[2] = 0;

    memset(&sMsg, 0, sizeof(sMsg));
    sMsg.tx_buf = sMsg.rx_buf = (unsigned long) uBuffer;
    sMsg.len = sizeof(uBuffer);
    sMsg.delay_usecs = 0;
    sMsg.speed_hz = Context->Speed;
    sMsg.bits_per_word = Context->Bits;

    *Val = 0;
    if(ioctl(Context->Fd, SPI_IOC_MESSAGE(1), &sMsg) < 0) 
        return errno;

    *Val = (uBuffer[2] ^ 0xff);
    return 0;
}


static int 
_piface_write(PIFACE *Context, uint8_t Reg, uint8_t Val) {
    struct spi_ioc_transfer sMsg;
    uint8_t uBuffer[3];

    //  Control Byte: 0 1 0 0 A2 A1 A0 0

    uBuffer[0] = 0x40 | ((Context->Address << 1) & 0xe);
    uBuffer[1] = Reg;
    uBuffer[2] = Val;

    memset(&sMsg, 0, sizeof(sMsg));
    sMsg.tx_buf = sMsg.rx_buf = (unsigned long) uBuffer;
    sMsg.len = sizeof(uBuffer);
    sMsg.delay_usecs = 0;
    sMsg.speed_hz = Context->Speed;
    sMsg.bits_per_word = Context->Bits;

    if(ioctl(Context->Fd, SPI_IOC_MESSAGE(1), &sMsg) < 0)
        return errno;
    return 0;
}


int
piface_initialise(ECHIDNA *Context) {
    PIFACE *pContext;
    int nResult;

    errno = 0;
    if((pContext = calloc(1, sizeof(PIFACE))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return errno;
    }
    pContext->Address = 0;
    pContext->Bits = 8;
    pContext->Speed = 10000000;

    if((pContext->Fd = open("/dev/spidev0.0", O_RDWR)) < 0) {
        log_error("Error opening SPI device: %s", strerror(errno));
        goto error;
    }
   
    //  Configure SPI mode 0, 8-bits, 10 MHz
    if((ioctl(pContext->Fd, SPI_IOC_WR_MODE, &(int){0}) < 0) ||
            (ioctl(pContext->Fd, SPI_IOC_WR_BITS_PER_WORD, &pContext->Bits) < 0) ||
            (ioctl(pContext->Fd, SPI_IOC_WR_MAX_SPEED_HZ, &pContext->Speed) < 0)) {

        log_error("Error configuring SPI device: %s", strerror(errno));
        goto error;
    }
    if(((nResult = _piface_write(pContext, REG_IOCON, 40)) != 0) ||
            ((nResult = _piface_write(pContext, REG_IODIRA, 0)) != 0) ||
            ((nResult = _piface_write(pContext, REG_IODIRB, 255)) != 0) ||
            ((nResult = _piface_write(pContext, REG_GPPUB, 255)) != 0)) {
        errno = nResult;
        goto error;
    }

    echidna_register(Context, "piface_read", TYPE_FUNCTION, piface_read, pContext);
    echidna_register(Context, "piface_write", TYPE_FUNCTION, piface_write, pContext);

    log_info("Registered Raspberry PiFace hardware");

    return 0;

error:
    if(pContext->Fd >= 0)
        close(pContext->Fd);
    free(pContext);
    return errno;
}


int
piface_read(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PIFACE *pContext;
    uint8_t uByte;

    pContext = (PIFACE *) User;
    assert(pContext != NULL);
    _piface_read(pContext, REG_INPUT, &uByte);
    value_assign(Result, TYPE_BYTE, uByte);

    return 0;
}


int
piface_write(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    PIFACE *pContext;
    VALUE sValue;
    int nResult;

    pContext = (PIFACE *) User;
    assert(pContext != NULL);

    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return ERROR_PARAMETER_COUNT;
    value_copy(&sValue, &pParameter->Value);
    if(cast_byte(&sValue) != 0)
        return ERROR_PARAMETER_TYPE;

    nResult = _piface_write(pContext, REG_OUTPUT, sValue.Value.B8);
    value_assign(Result, TYPE_BOOL, (nResult == 0));

    return 0;
}
#else
static uint8_t data = 0;
static int piface_read(ECHIDNA* Context, const char* Name, LL* Parameters, VALUE* Result, void* User) {
  uint8_t uByte;

  uByte = data;
  printf("###read %02X\n", uByte);
  value_assign(Result, TYPE_BYTE, uByte);

  return 0;
}


static int piface_write(ECHIDNA* Context, const char* Name, LL* Parameters, VALUE* Result, void* User) {
  PARAMETER* pParameter;
  VALUE sValue;
  int nResult = 0;

  ll_reset(Parameters);
  if ((pParameter = ll_iterate(Parameters)) == NULL)
    return RT_ERR_PARAMETER_COUNT;
  value_copy(&sValue, &pParameter->Value);
  if (cast_byte(&sValue) != 0)
    return RT_ERR_PARAMETER_TYPE;

  data = sValue.Value.B8;
  printf("###write %02X\n", sValue.Value.B8);

  value_assign(Result, TYPE_BOOL, (nResult == 0));

  return 0;
}

int
piface_initialise(ECHIDNA *Context) {
    PIFACE *pContext;

    errno = 0;
    if((pContext = calloc(1, sizeof(PIFACE))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return errno;
    }
    pContext->Address = 0;
    pContext->Bits = 8;
    pContext->Speed = 10000000;

    echidna_register(Context, "piface_read", TYPE_FUNCTION, piface_read, NULL);
    echidna_register(Context, "piface_write", TYPE_FUNCTION, piface_write, NULL);

    log_info("Registered Raspberry PiFace hardware");

    return 0;
}
#endif