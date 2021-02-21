SUMMARY = "Maintec"
SECTION = "maintec"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "celix telnet"

SRCREV = "${AUTOREV}"

SRC_URI = "git://github.com/sjgarani/maintec.git;branch=main;protocol=git"

S = "${WORKDIR}/git"

inherit pkgconfig cmake

EXTRA_OECMAKE = ""

do_install() {
    install -d ${D}${bindir}
    install -m 0755 deploy/maintec/maintec ${D}${bindir}
    install -d ${D}${bindir}${CELIX_BUNDLES_PATH}
    install -m 0755 deploy/maintec/bundles/* ${D}${bindir}${CELIX_BUNDLES_PATH}
}