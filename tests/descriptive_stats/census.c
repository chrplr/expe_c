#include <apop.h>
int main(){
    apop_text_to_db(.text_file="ss08pdc.csv", .tabname="dc");
    apop_data *data = apop_query_to_data("select log(pincp+10) as log_income, agep, sex "
                    "from dc where agep+ pincp+sex is not null and pincp>=0");
    apop_model *est = apop_estimate(data, apop_ols);
    apop_model_print(est);
}
