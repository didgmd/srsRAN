/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#ifndef SRSLTE_UE_RRC_INTERFACES_H
#define SRSLTE_UE_RRC_INTERFACES_H

#include "phy_interface_types.h"
#include "rrc_interface_types.h"
#include "srslte/asn1/asn1_utils.h"
#include "srslte/common/byte_buffer.h"
#include "srslte/common/tti_point.h"

namespace srsue {

class rrc_interface_mac_common
{
public:
  virtual void ra_problem() = 0;
};

class rrc_interface_mac : public rrc_interface_mac_common
{
public:
  virtual void ra_completed()      = 0;
  virtual void release_pucch_srs() = 0;
};

class rrc_eutra_interface_rrc_nr
{
public:
  virtual void new_cell_meas_nr(const std::vector<phy_meas_nr_t>& meas) = 0;
  virtual void nr_rrc_con_reconfig_complete(bool status)                = 0;
};

class rrc_interface_phy_lte
{
public:
  virtual void in_sync()                                          = 0;
  virtual void out_of_sync()                                      = 0;
  virtual void new_cell_meas(const std::vector<phy_meas_t>& meas) = 0;

  typedef struct {
    enum { CELL_FOUND = 0, CELL_NOT_FOUND, ERROR } found;
    enum { MORE_FREQS = 0, NO_MORE_FREQS } last_freq;
  } cell_search_ret_t;

  virtual void cell_search_complete(cell_search_ret_t ret, phy_cell_t found_cell) = 0;
  virtual void cell_select_complete(bool status)                                  = 0;
  virtual void set_config_complete(bool status)                                   = 0;
  virtual void set_scell_complete(bool status)                                    = 0;
};

class rrc_interface_nas
{
public:
  virtual ~rrc_interface_nas()                                                          = default;
  virtual void        write_sdu(srslte::unique_byte_buffer_t sdu)                       = 0;
  virtual uint16_t    get_mcc()                                                         = 0;
  virtual uint16_t    get_mnc()                                                         = 0;
  virtual void        enable_capabilities()                                             = 0;
  virtual bool        plmn_search()                                                     = 0;
  virtual void        plmn_select(srslte::plmn_id_t plmn_id)                            = 0;
  virtual bool        connection_request(srslte::establishment_cause_t cause,
                                         srslte::unique_byte_buffer_t  dedicatedInfoNAS) = 0;
  virtual void        set_ue_identity(srslte::s_tmsi_t s_tmsi)                          = 0;
  virtual bool        is_connected()                                                    = 0;
  virtual void        paging_completed(bool outcome)                                    = 0;
  virtual std::string get_rb_name(uint32_t lcid)                                        = 0;
  virtual uint32_t    get_lcid_for_eps_bearer(const uint32_t& eps_bearer_id)            = 0;
  virtual bool        has_nr_dc()                                                       = 0;
};

class rrc_interface_pdcp
{
public:
  virtual void        write_pdu(uint32_t lcid, srslte::unique_byte_buffer_t pdu)     = 0;
  virtual void        write_pdu_bcch_bch(srslte::unique_byte_buffer_t pdu)           = 0;
  virtual void        write_pdu_bcch_dlsch(srslte::unique_byte_buffer_t pdu)         = 0;
  virtual void        write_pdu_pcch(srslte::unique_byte_buffer_t pdu)               = 0;
  virtual void        write_pdu_mch(uint32_t lcid, srslte::unique_byte_buffer_t pdu) = 0;
  virtual std::string get_rb_name(uint32_t lcid)                                     = 0;
};

class rrc_interface_rlc
{
public:
  virtual void        max_retx_attempted()                                       = 0;
  virtual std::string get_rb_name(uint32_t lcid)                                 = 0;
  virtual void        write_pdu(uint32_t lcid, srslte::unique_byte_buffer_t pdu) = 0;
};

class rrc_nr_interface_rrc
{
public:
  virtual void get_eutra_nr_capabilities(srslte::byte_buffer_t* eutra_nr_caps)   = 0;
  virtual void get_nr_capabilities(srslte::byte_buffer_t* nr_cap)                = 0;
  virtual void phy_set_cells_to_meas(uint32_t carrier_freq_r15)                  = 0;
  virtual void phy_meas_stop()                                                   = 0;
  virtual bool rrc_reconfiguration(bool                endc_release_and_add_r15,
                                   bool                nr_secondary_cell_group_cfg_r15_present,
                                   asn1::dyn_octstring nr_secondary_cell_group_cfg_r15,
                                   bool                sk_counter_r15_present,
                                   uint32_t            sk_counter_r15,
                                   bool                nr_radio_bearer_cfg1_r15_present,
                                   asn1::dyn_octstring nr_radio_bearer_cfg1_r15) = 0;
  virtual bool is_config_pending()                                               = 0;
};

} // namespace srsue

#endif // SRSLTE_UE_RRC_INTERFACES_H