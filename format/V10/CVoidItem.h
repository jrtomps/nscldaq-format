
#ifndef NSCLDAQ10_CVOIDITEM_H
#define NSCLDAQ10_CVOIDITEM_H

namespace DAQ {
namespace V10 {

class CVoidItem : public CRingItem
{
  public:
    CVoidItem() : CRingItem(UNDEFINED) {}

    uint32_t type() const { return UNDEFINED; }
};

} // end V10
} // end DAQ

#endif
