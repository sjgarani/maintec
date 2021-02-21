SUMMARY = "Maintec"
SECTION = "maintec"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "celix"

SRCREV = "${AUTOREV}"

SRC_URI = "git://github.com/sjgarani/maintec.git;branch=main;protocol=git"

S = "${WORKDIR}/git"

inherit pkgconfig cmake

EXTRA_OECMAKE = ""

export CELIX_BUNDLES_PATH="/usr/share/celix/bundles"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 deploy/maintec/maintec ${D}${bindir}
    install -d ${D}$CELIX_BUNDLES_PATH
    install -m 0755 deploy/maintec/bundles/maintec_main.zip ${D}$CELIX_BUNDLES_PATH
}

FILES_${PN} += "/usr/share/celix/bundles/maintec_main.zip"