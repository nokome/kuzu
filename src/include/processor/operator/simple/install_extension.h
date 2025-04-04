#pragma once

#include "extension/extension_installer.h"
#include "processor/operator/simple/simple.h"

namespace kuzu {
namespace processor {

struct InstallExtensionPrintInfo final : OPPrintInfo {
    std::string extensionName;

    explicit InstallExtensionPrintInfo(std::string extensionName)
        : extensionName{std::move(extensionName)} {}

    std::string toString() const override;

    std::unique_ptr<OPPrintInfo> copy() const override {
        return std::unique_ptr<InstallExtensionPrintInfo>(new InstallExtensionPrintInfo(*this));
    }

private:
    InstallExtensionPrintInfo(const InstallExtensionPrintInfo& other)
        : OPPrintInfo{other}, extensionName{other.extensionName} {}
};

class InstallExtension final : public Simple {
    static constexpr PhysicalOperatorType type_ = PhysicalOperatorType::INSTALL_EXTENSION;

public:
    InstallExtension(extension::InstallExtensionInfo info, const DataPos& outputPos, uint32_t id,
        std::unique_ptr<OPPrintInfo> printInfo)
        : Simple{type_, outputPos, id, std::move(printInfo)}, info{std::move(info)} {}

    void executeInternal(ExecutionContext* context) override;
    std::string getOutputMsg() override;

    std::unique_ptr<PhysicalOperator> copy() override {
        return std::make_unique<InstallExtension>(info, outputPos, id, printInfo->copy());
    }

private:
    void installExtension(main::ClientContext* context);

private:
    extension::InstallExtensionInfo info;
};

} // namespace processor
} // namespace kuzu
