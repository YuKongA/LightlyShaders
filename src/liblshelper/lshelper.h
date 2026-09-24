#include "liblshelper_export.h"

#include <effect/effecthandler.h>
#include <QRegion>
#include <QImage>
#include <QHash>
#include <QPainterPath>
#include <QStringList>

template <typename T> int signum(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace KWin {

class LIBLSHELPER_EXPORT LSHelper: public QObject
{
    Q_OBJECT

	public:
		LSHelper();
		~LSHelper();

		void reconfigure();
		QPainterPath superellipse(float size, int n, int translate);
    	QImage genMaskImg(int size, bool mask, bool outer_rect);
		void roundBlurRegion(EffectWindow *w, QRegion *region);
		bool isManagedWindow(EffectWindow *w);
		bool isExcludedWindow(EffectWindow *w) const;
		void windowDeleted(EffectWindow *w);
		void blurWindowAdded(EffectWindow *w);
		void blurWindowDeleted(EffectWindow *w);
		int roundness();

		enum { RoundedCorners = 0, SquircledCorners };
		enum { TopLeft = 0, TopRight, BottomRight, BottomLeft, NTex };

		QRegion* m_maskRegions[NTex];

	private:
		struct ExclusionRule {
			QString pattern;
			bool matchWindow;
			bool matchProcess;
		};

		QString processIdentityForWindow(EffectWindow *w) const;
		bool hasShadow(EffectWindow *w);
		void setMaskRegions();
		QRegion* createMaskRegion(QImage img, int size, int corner);

		int m_size, m_cornersType, m_squircleRatio, m_shadowOffset;
		bool m_disabledForMaximized;
		QList<ExclusionRule> m_exclusionRules;
		mutable QHash<EffectWindow *, QString> m_processIdentities;
		QList<EffectWindow *> m_managed;
};

} //namespace